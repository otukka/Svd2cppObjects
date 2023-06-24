

import xmltodict

from jinja2 import Environment, FileSystemLoader
from collections import defaultdict
import argparse
import json
from pathlib import Path


def peripheral(data, output):

    data['NAME'] = str(data['name']).upper()

    env = Environment(
        loader=FileSystemLoader('src/templates'),
        trim_blocks=True,
        lstrip_blocks=True
    )

    template = env.get_template('peripheral.j2')

    with open(Path.joinpath(output, data['name']+'.hpp'), 'w') as f:
        f.write(template.render(data))


def main(args):

    p = Path(args.filename)
    o = Path(args.output)

    if not o.exists():
        o.mkdir()


    with open(p, 'r') as f:
        data = xmltodict.parse(f.read(), force_list={'field': {}, 'register': {}}, attr_prefix='attr_')

    if args.debug == True:

        with open(o+p.stem+'.json', 'w') as f:
            json.dump(data, f)

    for perph in data['device']['peripherals']['peripheral']:
        try:
            peripheral(perph, o)

        except Exception as e:
            print(e)


parser = argparse.ArgumentParser(description="")
parser.add_argument("filename", help="SVD file")
parser.add_argument("output", help="output folder")
parser.add_argument('--debug', action='store_true', help='Extra debug actions')

args = parser.parse_args()


if len(args.filename) != 0:
    main(args)
