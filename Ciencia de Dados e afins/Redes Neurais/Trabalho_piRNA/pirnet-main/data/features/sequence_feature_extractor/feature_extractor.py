# -*- coding: utf-8 -*-

import argparse
import os
import shutil
import subprocess
import sys

import numpy  as np
import pandas as pd


def extract_kmers(filename, type):
    prefix = filename[slice(0, 3)]
    for k in range(1, 5):
        command = [
            'python '
            'Pse-in-One-2.0/nac.py '
            '{filename} DNA kmer '
            '-k {k} -f csv -out tmp/{type}_{prefix}_k{k}.csv'.format(filename=filename,
                                                              k=k,
                                                              type=type,
                                                              prefix=prefix)
        ]
        subprocess.call(command, shell=True)


def extract_mismatch(filename, type):
    prefix = filename[slice(0, 3)]
    for k, m in zip([1, 2, 3, 4], [0, 1, 1, 1]):
        command = [
            'python '
            'Pse-in-One-2.0/nac.py '
            '{filename} DNA mismatch '
            '-m {m} -k {k} -f csv -out tmp/{type}_{prefix}_m{k}.csv'.format(filename=filename,
                                                                     m=m,
                                                                     k=k,
                                                                     type=type,
                                                                     prefix=prefix)
        ]
        subprocess.call(command, shell=True)


def extract_subsequence(filename, type):
    prefix = filename[slice(0, 3)]
    for k in range(1, 5):
        command = [
            'python '
            'Pse-in-One-2.0/nac.py '
            '{filename} DNA subsequence '
            '-k {k} -f csv -out tmp/{type}_{prefix}_s{k}.csv'.format(filename=filename,
                                                              k=k,
                                                              type=type,
                                                              prefix=prefix)
        ]
        subprocess.call(command, shell=True)


def extract_features(filename, type):
    print('Extracting k-mers (k from 1 to 4)')
    extract_kmers(filename, type)
    print('Extracting mismatch (k from 1 to 4, m from 0 to 1)')
    extract_mismatch(filename, type)
    print('Extracting subsequence (k from 1 to 4)')
    extract_subsequence(filename, type)


def getFiles(feature):
    files = os.listdir('tmp/')
    pos_files = list()
    neg_files = list()
    for file in files:
        prefix = file[0:3]
        letter = file[-6]
        if letter == feature:
            if prefix == 'pos':
                pos_files.append(file)
                pos_files.sort()
            elif prefix == 'neg':
                neg_files.append(file)
                neg_files.sort()
            else:
                pass
    
    return pos_files, neg_files


def mergeHorizontally(files, label):
    data = list()
    for file in files:
        df = pd.read_csv('tmp/' + file, header=None)
        data.append(df)
    df = pd.concat(data, axis=1)
    # n_rows, n_cols = df.shape
    # df.insert(n_cols, n_cols, label)
    
    return df


def mergeVertically(pos_data, neg_data):
    return pd.concat([pos_data, neg_data], axis=0)


def mergeFiles(feature):
    if feature == 'kmers':
        pos_files, neg_files = getFiles('k')
    elif feature == 'mismatch':
        pos_files, neg_files = getFiles('m')
    elif feature == 'subsequence':
        pos_files, neg_files = getFiles('s')
    else:
        pass
        
    pos_data = mergeHorizontally(pos_files, 1)
    neg_data = mergeHorizontally(neg_files, 0)
    # data = mergeVertically(pos_data, neg_data)
        
    return pos_data, neg_data



def do_extraction(args):
    DIR = 'Pse-in-One-2.0'
    ZIPFILE = 'Pse-in-One-2.0.zip'

    if os.path.exists(DIR):
        print('Diretório {dir} encontrado'.format(dir=DIR))
    else:
        if os.path.exists(ZIPFILE):
            print('Arquivio {zip} encontrado. Extraindo...'.format(zip=ZIPFILE))
            subprocess.call(['unzip', ZIPFILE])
            print('Extração completa!')
        else:
            print('Não foi possível encontrar o diretório {dir} ou o arquivo {zip}')
            print('Encerrando a execução do programa')
            sys.exit()

    POS_FILE = args.pos_samples
    NEG_FILE = args.neg_samples
    
    if not os.path.exists(POS_FILE):
        print('Positive samples (pos) not found!'.format(pos=POS_FILE))
        print('Aborting')
        sys.exit()
    
    if not os.path.exists(NEG_FILE):
        print('Negative samples (neg) not found!'.format(neg=NEG_FILE))
        print('Aborting')
        sys.exit()

    print('Creating temporary directory for operation')
    try:
        os.makedirs('tmp')
    except OSError:
        print('tmp directory already exists. All files in tmp will be deleted')
        shutil.rmtree('tmp')
        os.makedirs('tmp')

    print('Extracting features from positive samples')
    extract_features(POS_FILE, "pos")

    print('Extracting features from negative samples')
    extract_features(NEG_FILE, "neg")

    features = ['kmers', 'mismatch', 'subsequence']
    for feature in features:
        pos_file, neg_file = mergeFiles(feature)
        # standardized_data = standardscaler(data)
        # normalized_data   = minmaxscaler(data)
        pos_file.to_csv("pos_" + feature + '_raw.csv', index=False, header=False, float_format='%.7f')
        neg_file.to_csv("neg_" + feature + '_raw.csv', index=False, header=False, float_format='%.7f')
        # standardized_data.to_csv(feature + '-standard.csv', index=False, header=False, float_format='%.5f')
        # normalized_data.to_csv(feature + '-normal.csv', index=False, header=False, float_format='%.5f')
    
    print('Deleting temporary files')
    shutil.rmtree('tmp')
    print('Feature extraction completed!')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('-p',
                        '--pos',
                        type=str,
                        action='store',
                        dest='pos_samples',
                        required=True)

    parser.add_argument('-n',
                        '--neg',
                        type=str,
                        action='store',
                        dest='neg_samples',
                        required=True)
    
    args = parser.parse_args()
    do_extraction(args)

