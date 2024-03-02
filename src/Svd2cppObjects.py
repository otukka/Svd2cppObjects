

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


def factory(data, output):

    data['NAME'] = str(data['name']).upper()

    env = Environment(
        loader=FileSystemLoader('src/templates'),
        trim_blocks=True,
        lstrip_blocks=True
    )

    template = env.get_template('factory.j2')

    with open(Path.joinpath(output, data['name']+'.hpp'), 'w') as f:
        f.write(template.render(data))


def test_app(data, output):

    data['NAME'] = str(data['name']).upper()

    env = Environment(
        loader=FileSystemLoader('src/templates'),
        trim_blocks=True,
        lstrip_blocks=True
    )

    template = env.get_template('test.j2')

    with open(Path.joinpath(output, 'test.cpp'), 'w') as f:
        f.write(template.render(data))


def main(args):

    p = Path(args.filename)
    o = Path(args.output)

    if not o.exists():
        o.mkdir()

    with open(p, 'r') as f:
        data = xmltodict.parse(f.read(), force_list={
                               'field': {}, 'register': {}}, attr_prefix='attr_')

    if args.debug == True:

        with open(o+p.stem+'.json', 'w') as f:
            json.dump(data, f)

    for perph in data['device']['peripherals']['peripheral']:
        if ('attr_derivedFrom' in perph):
            
            perph['groupName'] = list(filter(lambda x: x['name'] == perph['attr_derivedFrom'], data['device']['peripherals']['peripheral']))[0]['groupName']
        if perph['name'] == 'GPIOH':
            print(perph)
        peripheral(perph, o)

    factory(data['device'], o)

    test_app(data['device'], o)


parser = argparse.ArgumentParser(description="")
parser.add_argument("filename", help="SVD file")
parser.add_argument("output", help="output folder")
parser.add_argument('--debug', action='store_true', help='Extra debug actions')

args = parser.parse_args()


if len(args.filename) != 0:
    main(args)
