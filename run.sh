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

rm -rf out/*

cd ${ROOT_DIR} && python ${ROOT_DIR}/src/Svd2cppObjects.py $1 $2

deactivate

# Sanity check app
g++ -std=gnu++14 --save-temps -I./out -I./inc -m32 -g -Wall -Wpedantic -Wconversion -Werror -DTEST_CODE -DDEV_DEBUG -DSYSTEM_BIT_WIDTH=SYSTEM_32_BIT out/test_app.cpp -o out/test_app || exit -1

./out/test_app