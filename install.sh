#! /bin/bash

PYTHONVERSION="3.9.0"

ROOT="$(dirname "$(readlink -fm "$0")")"

cd "$ROOT"

if [[ -d "env" ]]; then
    rm -rf env
fi

mkdir env

python3 -m virtualenv "$ROOT"/env/ || exit 1

source "$ROOT"/env/bin/activate || exit 1

pip install --upgrade pip

pip install -r requirements.txt

deactivate
