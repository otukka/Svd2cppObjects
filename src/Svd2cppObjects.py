

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

    template = env.get_template('test_app.j2')

    with open(Path.joinpath(output, 'test_app.cpp'), 'w') as f:
        f.write(template.render(data))


def main(args):

    p = Path(args.filename)
    o = Path(args.output)

    if not o.exists():
        o.mkdir()

    with open(p, 'r') as f:
        data = xmltodict.parse(
            f.read(), attr_prefix='attr_', force_list=['register', 'field'])

    for perph in data['device']['peripherals']['peripheral']:
        if 'attr_derivedFrom' in perph:

            perph['groupName'] = list(filter(lambda x: x['name'] == perph['attr_derivedFrom'],
                                      data['device']['peripherals']['peripheral']))[0]['groupName']

        if 'registers' in perph:
            for reg in perph['registers']['register']:
                if not 'fields' in reg:
                    reg['fields'] = {'field': []}

                if len(reg['fields']['field']) == 0:
                    reg['fields']['field'].append(
                        {
                            "name": "SOMETHING_ODD",
                            "description": "See the reference manual",
                            "bitOffset": "0",
                            "bitWidth": "32"
                        }
                    )

    if args.debug == True:
        with open(o+p.stem+'.json', 'w') as f:
            json.dump(data, f)

    for perph in data['device']['peripherals']['peripheral']:
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
