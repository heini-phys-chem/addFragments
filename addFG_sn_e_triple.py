import sys
import os
import re
import openbabel as ob

def opt_mmff_FG(mol, numAtoms, outfile):
  # initialize force field and constraint classes
  MMFF = ob.OBForceField.FindType("MMFF94")
  constraints = ob.OBFFConstraints()
  conv = ob.OBConversion()

  # setup force field
  MMFF.Setup(mol)

  # add constraints
  [constraints.AddAtomConstraint(i) for i in range(1,numAtoms)]
  MMFF.SetConstraints(constraints)

  # run optization 
  MMFF.ConjugateGradients(1000)

  # update coordinates
  MMFF.UpdateCoordinates(mol)

  # write to xyz file
  print outfile
  conv.WriteFile(mol, "double/" + outfile)

  # clear mol class
  mol.Clear()

def exchangeAtom(C,H,molTS,molFG,outfile, bondLength):
  # read write xyz file
  convTS,convFG = [ob.OBConversion() for i in range(2)]
  convTS.SetInAndOutFormats("xyz","xyz")
  convFG.SetInAndOutFormats("xyz","xyz")

  # builder
  builder = ob.OBBuilder()

  # define molecules, atoms and bond classes
  TS,FG  = [ob.OBMol() for i in range(2)]
  atomH  = ob.OBAtom()
  atomC  = ob.OBAtom()
  bond   = ob.OBBond()

  # read in xyz files
  convTS.ReadFile(TS, molTS)
  convFG.ReadFile(FG, molFG)

  # number of atoms in TS molecule
  numAtoms = TS.NumAtoms()

  # get hydrogen atom and its vector
  atomH = TS.GetAtom(H)
  atomC = TS.GetAtom(C)
  vec = ob.vector3(float(atomH.GetX()), float(atomH.GetY()),float(atomH.GetZ()))

  # delete hydrogen atom
  TS.DeleteAtom(atomH)

  # put both molecules together (same coord system)
  TS += FG

  # making the bond
  builder.Connect(TS, C, numAtoms, vec, 1)

  bond = TS.GetBond(C,numAtoms)
  bond.SetLength(atomC, bondLength)

  # call opimizer
  #opt_mmff_FG(TS, numAtoms, outfile)

  convTS.WriteFile(TS, "triple/" + outfile)

  # clear TS and FG molecule classes
  TS.Clear()
  FG.Clear()

if __name__ == "__main__":

  filename = sys.argv[1]
  name = os.path.splitext(filename)[0]
  pathCoords = "/home/stefan/PhD/projects/reactions/sn_e/e2/data_set/coords/"
  functionalGroups = ["B.xyz","C.xyz","D.xyz","E.xyz"]

  print name

  pos1 = name.split('_')[1]
  pos2 = name.split('_')[2]
  pos3 = name.split('_')[3]
  pos4 = name.split('_')[4]

  if (pos1 != "A" and pos2 != "A"):
    C = [2,2]
    H = [5,6]
    pos = [3,4]
  if (pos1 != "A" and pos3 != "A"):
    C = [1,2]
    H = [5,6]
    pos = [2,4]
  if (pos1 != "A" and pos4 != "A"):
    C = [1,2]
    H = [5,6]
    pos = [2,3]
  if (pos2 != "A" and pos3 != "A"):
    C = [1,2]
    H = [5,6]
    pos = [1,4]
  if (pos2 != "A" and pos4 != "A"):
    C = [1,2]
    H = [5,6]
    pos = [1,3]
  if (pos3 != "A" and pos4 != "A"):
    C = [1,1]
    H = [5,6]
    pos = [1,2]

  print pos1, pos2, pos3, pos4

  for FG in functionalGroups:
    if FG == "D.xyz":
      bondLength = 1.54
    else:
      bondLength = 1.47

    for j,i in enumerate(pos):
      if i==1: pos1=os.path.splitext(FG)[0]
      if i==2: pos2=os.path.splitext(FG)[0]
      if i==3: pos3=os.path.splitext(FG)[0]
      if i==4: pos4=os.path.splitext(FG)[0]

      outfile = "product-sn2_" + pos1 + "_" + pos2 + "_" + pos3 + "_" + pos4 + "_0_A.xyz"
      print C[j], H[j]
      exchangeAtom(C[j], H[j], filename, pathCoords + FG, outfile, bondLength)

      pos1, pos2, pos3, pos4 = name.split('_')[1],name.split('_')[2],name.split('_')[3],name.split('_')[4]

