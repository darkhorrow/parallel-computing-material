import subprocess
import argparse

parser =  argparse.ArgumentParser()
parser.add_argument('-i', type=str, help='Input file to execute N times', required=True)
parser.add_argument('-o', type=str, help='Ouput file to store the results', required=True)
parser.add_argument('-n', type=int, help='Number of executions', required=True)
args = parser.parse_args()

results = []

for _ in range(args.n):
	results.append((subprocess.run([args.i], stdout=subprocess.PIPE)).stdout)

with open(args.o, 'wb') as output:
	for result in results:
		output.write(result)

print(f'Program finished. The output file is {args.o}')

