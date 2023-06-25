#! /bin/bash

usage () {
    echo "Usage: run.sh <path-to-SVD-file> <output-folder>"]
    exit 1
}

if [ -z "$1" ]; then
    usage
fi
if [ -z "$2" ]; then
    usage
fi

ROOT_DIR="$(dirname "$(readlink -fm "$0")")"


# PYTHONPATH
export PYTHONPATH=$ROOT_DIR:$PYTHONPATH

# Environment
source ${ROOT_DIR}/env/bin/activate

cd ${ROOT_DIR} && python ${ROOT_DIR}/src/Svd2cppObjects.py $1 $2

deactivate