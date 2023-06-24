#! /bin/bash

PYTHONVERSION="3.9.0"

ROOT="$(dirname "$(readlink -fm "$0")")"

CUSTOM_DIR="$ROOT/python/$PYTHONVERSION"


if [[ ! -d "$CUSTOM_DIR" ]]; then
    # Custom Python installation script

    mkdir -p "$CUSTOM_DIR"/tmp

    cd "$CUSTOM_DIR"/tmp

    wget https://www.python.org/ftp/python/"$PYTHONVERSION"/Python-"$PYTHONVERSION".tgz || exit 1

    tar -xzvf Python-"$PYTHONVERSION".tgz

    cd Python-"$PYTHONVERSION"

    ./configure --prefix="$CUSTOM_DIR"

    make install

    cd "$CUSTOM_DIR"

    rm -rf ./tmp
fi

cd "$ROOT"

if [[ -d "env" ]]; then
    rm -rf env
fi

mkdir env

# Custom Python install location
"$CUSTOM_DIR"/bin/python3 -m venv "$ROOT"/env/ || exit 1

source "$ROOT"/env/bin/activate || exit 1

pip install --upgrade pip

pip install -r requirements.txt

deactivate



