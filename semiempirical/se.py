#!/usr/bin/env python
""" wrapper script to evaluate semiempirical hamiltonians on xyz files """
import sys
from ase.calculators.mopac import MOPAC
from ase.io import read
import subprocess
import os

try:
	methods, coordinates = sys.argv[1:]
except:
	print ('Usage: %s METHODS coord.xyz' % sys.argv[0])
	exit(2)

mol = read(coordinates)
for method in methods.split(','):
	mol.calc = MOPAC(label='workfile', method=method, task='', relscf=None)
	mol.calc.write_input(mol)
	if method in 'OM1 OM2 OM3'.split():
		runner = './run_mndo.sh'
		col = 4
	else:
		runner = './run_mopac.sh'
		col = 5
	with open(os.devnull, 'w') as devnull:
		subprocess.call(runner, stdout=devnull, stderr=devnull)
	lines = open('workfile.out').readlines()
	valid = [_.strip().split()[col] for _ in lines if 'FINAL HEAT OF FORMATION' in _]
	if len(valid) != 1:
		continue
	print method, coordinates, valid[0]
	os.remove('workfile.out')
	try:
		os.remove('workfile.arc')
	except:
		pass
	os.remove('workfile.mop')
