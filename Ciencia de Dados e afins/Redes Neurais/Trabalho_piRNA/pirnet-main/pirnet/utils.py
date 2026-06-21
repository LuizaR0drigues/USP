from datetime import datetime
import logging
import os
import sys
import uuid

import pandas as pd


def create_results_folder(layers, activation, optimizer):
    timestamp = datetime.timestamp(datetime.now())
    foldername = f"{timestamp:.0f}_run-{layers}-{activation}-{optimizer}"

    folderpath = os.path.join(os.getcwd(), foldername)
    os.makedirs(folderpath, exist_ok=True)

    return folderpath


def create_logger(folderpath=None):
    if folderpath is None:
        folderpath = os.getcwd()

    filename = f"{uuid.uuid4()}.log"

    filehandler = logging.FileHandler(
        filename=os.path.join(folderpath, filename)
    )
    stdouthandler = logging.StreamHandler(sys.stdout)

    logging.basicConfig(
        level=logging.DEBUG,
        format="[%(asctime)s] {%(filename)s:%(lineno)d} %(levelname)s: %(message)s",
        handlers=[
            filehandler,
            stdouthandler,
        ]
    )

    return logging.getLogger()


def save_results(results, folderpath):
    df = pd.DataFrame(results)
    df = df.reset_index()
    df = df.rename(columns={"index": "fold"})

    filepath = os.path.join(folderpath, "results.csv")
    df.to_csv(filepath, index=False)
