import argparse
from statistics import NormalDist
import re


def confidence_interval(data, confidence=0.95):
    dist = NormalDist.from_samples(data)
    z = NormalDist().inv_cdf((1 + confidence) / 2.)
    h = dist.stdev * z / ((len(data) - 1) ** .5)
    return dist.mean, round((2*h)/dist.mean, 4)


parser = argparse.ArgumentParser()
parser.add_argument('-i', type=str, help='Input file to parse', required=True)
args = parser.parse_args()

results = []

with open(args.i, 'r') as input:
    i = 0
    init_time = []
    exec_time = []
    for line in input.readlines():
        token = re.split('seg|:', line)
        try:
            if i % 2 == 0:
                init_time.append(float(token[1]))
            else:
                exec_time.append(float(token[1]))
            i = i + 1
        except ValueError:
            pass

    print(confidence_interval(init_time))
    print(confidence_interval(exec_time))
