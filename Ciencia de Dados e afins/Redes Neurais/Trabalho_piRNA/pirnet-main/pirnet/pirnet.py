import argparse
import time
import os
import random

import numpy as np
import pandas as pd
import tensorflow as tf

from sklearn import metrics
from sklearn import model_selection
from sklearn import pipeline
from sklearn import preprocessing
from tensorflow.keras import models
from tensorflow.keras import layers
from tensorflow.keras.wrappers.scikit_learn import KerasClassifier

import utils


SEED_VALUE = 0
os.environ['PYTHONHASHSEED'] = str(SEED_VALUE)
random.seed(SEED_VALUE)
np.random.seed(SEED_VALUE)
tf.random.set_seed(SEED_VALUE)


EPOCHS = 128
BATCH_SIZE = 32
SCALERS = {
    "MinMaxScaler": preprocessing.MinMaxScaler(),
    "StandardScaler": preprocessing.StandardScaler(),
}


def specificity_score(y_true, y_pred, **kwargs):
    return metrics.recall_score(y_true, y_pred, pos_label=0, **kwargs)


def __add_label_last_column(samples, label):
    samples = samples.copy()
    col_size = len(samples.columns)
    samples[col_size] = label

    return samples


def load_data(
    pos_file,
    neg_file,
    shuffle=True,
    return_X_y=True
):
    pos_samples = pd.read_csv(pos_file, header=None)
    neg_samples = pd.read_csv(neg_file, header=None)

    pos_samples_and_label = __add_label_last_column(pos_samples, 1)
    neg_samples_and_label = __add_label_last_column(neg_samples, 0)

    _, n_cols_pos = pos_samples_and_label.shape
    _, n_cols_neg = neg_samples_and_label.shape

    if n_cols_pos != n_cols_neg:
        raise ValueError(
            f"Number of columns in positive samples ({n_cols_pos})"
            f"and negative samples ({n_cols_neg}) don't match!"
        )

    samples_and_label = pd.concat([pos_samples_and_label, neg_samples_and_label], axis="index")

    if shuffle:
        samples_and_label = (
            samples_and_label.sample(frac=1)
            .reset_index(drop=True)
        )

    if return_X_y:
        return (
            samples_and_label.iloc[:, :-1].values,
            samples_and_label.iloc[:, -1].values
        )

    return samples_and_label


def create_model(
    input_dim,
    n_layers,
    activation,
    optimizer,
):
    kernel_init = "he_normal" if activation == "relu" else "glorot_normal"

    model = models.Sequential([
        layers.Dense(input_dim=input_dim, units=340, activation=activation, kernel_initializer=kernel_init),
        layers.Dropout(0.5),
    ])
    for i in range(1, n_layers):
        model.add(layers.Dense(340, activation=activation, kernel_initializer=kernel_init))
        model.add(layers.Dropout(0.5))

    model.add(layers.Dense(units=1, activation="sigmoid", kernel_initializer="glorot_normal"))

    model.compile(
        optimizer=optimizer,
        loss="binary_crossentropy",
        metrics=["binary_accuracy"],
    )

    return model


def build_model(
    X, y,
    scaler,
    n_layers, activation, optimizer,
    eval_metrics,
    n_folds=10,
):
    _, n_features = X.shape

    transformer = SCALERS.get(scaler)
    if transformer is None:
        print(f"Scaler {scaler} doens't exists. Setting MinMaxScaler")
        transformer = SCALERS.get("MinMaxScaler")

    model = KerasClassifier(
        build_fn=create_model,
        input_dim=n_features,
        n_layers=n_layers, activation=activation, optimizer=optimizer,
        batch_size=BATCH_SIZE, epochs=EPOCHS,
        verbose=0
    )

    pipe = pipeline.Pipeline([
        ("transform", transformer),
        ("model", model),
    ])

    cv_results = model_selection.cross_validate(
        pipe,
        X, y,
        scoring=eval_metrics,
        cv=n_folds,
    )
    return cv_results


def main(args):
    folderpath = utils.create_results_folder(args.n_layers, args.activation, args.optimizer)
    logger = utils.create_logger(folderpath)
    logger.info(f"Results will be stored into {folderpath}")

    logger.info("Importing data...")
    X, y = load_data(args.pos_file, args.neg_file)
    logger.info("Done!")

    eval_metrics = {
        "accuracy": metrics.make_scorer(metrics.balanced_accuracy_score),
        "specificity": metrics.make_scorer(specificity_score),
        "sensivity": metrics.make_scorer(metrics.recall_score),
        "precision": metrics.make_scorer(metrics.precision_score),
        "f1": metrics.make_scorer(metrics.f1_score),
        "mcc": metrics.make_scorer(metrics.matthews_corrcoef),
    }

    logger.info("Starting cross-validation... (this may take a while)")
    logger.info(
        "Using...\n"
        f"pos_file: {args.pos_file}\n"
        f"neg_file: {args.neg_file}\n"
        f"scaler: {args.scaler}\n"
        f"n_layers: {args.n_layers}\n"
        f"activation: {args.activation}\n"
        f"optimizer: {args.optimizer}"
    )
    results = build_model(
        X, y,
        args.scaler,
        args.n_layers, args.activation, args.optimizer,
        eval_metrics,
        args.n_folds,
    )
    logger.info("Done!")

    logger.info(f"Saving results into {folderpath}")
    utils.save_results(results, folderpath)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='', allow_abbrev=False)
    parser.add_argument(
        '-p', '--pos_file',
        type=str,
        action='store',
        dest='pos_file',
        required=True,
        help='Path to positive features file'
    )
    parser.add_argument(
        '-n', '--neg_file',
        type=str,
        action='store',
        dest='neg_file',
        required=True,
        help='Path to negative features file'
    )
    parser.add_argument(
        '-k', '--n_folds',
        type=int,
        action='store',
        dest='n_folds',
        required=False,
        default=10,
        help='Path to output directory'
    )
    parser.add_argument(
        '-s', '--scaler',
        type=str,
        choices=['MinMaxScaler', 'StandardScaler'],
        action='store',
        dest='scaler',
        required=True,
        help='Data scaler'
    )
    parser.add_argument(
        '-l', '--n_layers',
        type=int,
        choices=[3, 5],
        action='store',
        dest='n_layers',
        required=True,
        help='Neural network number of layers'
    )
    parser.add_argument(
        '-a', '--activation',
        type=str,
        choices=['relu', 'sigmoid'],
        action='store',
        dest='activation',
        required=True,
        help='Neural network activation function'
    )
    parser.add_argument(
        '-o', '--optimizer',
        type=str,
        choices=['adam', 'sgd'],
        action='store',
        dest='optimizer',
        required=True,
        help='Neural network optimizer'
    )

    args = parser.parse_args()

    print("Starting training!")
    start_time = time.time()
    main(args)
    minutes = (time.time() - start_time) / 60
    seconds = (time.time() - start_time) % 60
    print("Process completed!\n"
          f"Time: {minutes:.0f} minute(s) and {seconds:.0f} second(s)")
