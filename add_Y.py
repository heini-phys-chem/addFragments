import sys
import numpy as np
import openbabel as ob
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_style('whitegrid')

def move_Nuc(rxn, fin, fout, d):
	conv	= ob.OBConversion()
	mol		= ob.OBMol()
	C1		= ob.OBAtom
	C2		= ob.OBAtom
	X			= ob.OBAtom
	H			= ob.OBAtom
	Nuc		= ob.OBAtom

	conv.SetInAndOutFormats('xyz','xyz')
	conv.ReadFile(mol,fin)

	numAtoms	= mol.NumAtoms()

	C1		= mol.GetAtom(1)
	C2		= mol.GetAtom(2)
	X			= mol.GetAtom(3)
	H			= mol.GetAtom(4)

	if rxn == "Sn2":
		vecC		= np.asarray([ C1.GetX(), C1.GetY(), C1.GetZ() ])
		vecCX		= np.asarray([ C1.GetX() - X.GetX(), C1.GetY() - X.GetY(), C1.GetZ() - X.GetZ() ])
		normCX	= np.linalg.norm(vecCX)
		vecY		= vecC + d*(vecCX/normCX)
		Nuc = mol.GetAtom(numAtoms)
		Nuc.SetVector(vecY[0], vecY[1], vecY[2])

	elif rxn == "E2":
		vecC		= np.asarray([ C2GetX(), C2.GetY(), C2.GetZ() ])
		vecCH		= np.asarray([ C2.GetX() - X.GetX(), R2GetY() - X.GetY(), C2.GetZ() - X.GetZ() ])
		vecCH		*= (-1)
		normCH	= np.linalg.norm(vecCH)
		vecY		= vecC + d*(vecCX/normCH)
		Nuc = mol.GetAtom(numAtoms)
		Nuc.SetVector(vecY[0], vecY[1], vecY[2])

	conv.WriteFile(mol,fout)

def hist(x):
	plt.hist(x, 50, facecolor='g')
	plt.show()

if __name__ == "__main__":

	filename = sys.argv[1]

	f = open(filename, 'r')
	lines = f.readlines()
	f.close()

	targets		= []
	barriers	= []
	ds				= []

	for line in lines:
		tokens = line.split(',')

		if float(tokens[9]) > -100 and float(tokens[9]) < 100:
			targets.append(tokens[3])
			ds.append(float(tokens[7]))
			barriers.append(float(tokens[9]))

	#hist(ds)
	#exit(0)

	for i,target in enumerate(targets):
		'''		CHOOSE THE CORRECT REACTION (Sn2 OR E2) and also the output name accodding to the reaction!!!!!!
		'''
		fin		= target + ".xyz"
		fout	= target + "_Sn2.xyz"
		rxn = "Sn2"

		move_Nuc(rxn, fin, fout, ds[i])
