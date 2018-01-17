import sys
import glob
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
    conv.WriteFile(mol, "../out_xyz/" + outfile)

    # clear mol class
    mol.Clear()

def exchangeAtom(C,H,molTS,molFG,outfile):
    # read write xyz file
    convTS,convFG = [ob.OBConversion() for i in range(2)]
    convTS.SetInAndOutFormats("xyz","xyz")
    convFG.SetInAndOutFormats("xyz","xyz")

    # builder
    builder = ob.OBBuilder()

    # define molecules, atoms and bond classes
    TS,FG = [ob.OBMol() for i in range(2)]
    atomH = ob.OBAtom
    bond = ob.OBBond()

    # read in xyz files
    convTS.ReadFile(TS, molTS)
    convFG.ReadFile(FG, molFG)

    # number of atoms in TS molecule
    numAtoms = TS.NumAtoms()

    # get hydrogen atom and its vector
    atomH = TS.GetAtom(H)
    vec = ob.vector3(float(atomH.GetX()), float(atomH.GetY()),float(atomH.GetZ()))

    # delete hydrogen atom
    TS.DeleteAtom(atomH)

    # put both molecules together (same coord system)
    TS += FG

    # making the bond
    builder.Connect(TS, C, numAtoms, vec, 1)

    # call opimizer
    opt_mmff_FG(TS, numAtoms, outfile)

    # clear TS and FG molecule classes
    TS.Clear()
    FG.Clear()

if __name__ == "__main__":

    filename = sys.argv[1]
    pathCoords = "/home/stefan/PhD/projects/reactions/claisen/data_set/coords/"
    functionalGroups = ["br.xyz","cbr3.xyz","ccl3.xyz","cf3.xyz","ch3.xyz","cl.xyz","cn.xyz","coh.xyz","cooh.xyz","f.xyz","nh2.xyz","no2.xyz","och3.xyz","oh.xyz","ph.xyz"]

    print filename

    pos1 = filename.split('_')[0]
    print "pos1: " + str(pos1)
    FG1 = (filename.split('_')[1])[:-4]
    print "FG1: " + str(FG1)

    if pos1 == "2.2":
        lst_pos2 = ["3","4.1","4.2","5","6.2","6.1"]
        lst_C = [3,4,4,5,6,6]
        lst_H = [8,9,10,11,13,12]
        for FG2xyz in functionalGroups:
            FG2 = FG2xyz[:-4]
            for i,pos2 in enumerate(lst_pos2):
                outfile = str(pos1) + "_" + str(FG1) + "_" + str(pos2) + "_" + str(FG2) + ".xyz"
                exchangeAtom(lst_C[i],lst_H[i],filename,pathCoords + FG2xyz,outfile)

    if pos1 == "3":
        lst_pos2 = ["4.1","4.2","5","6.2","6.1"]
        lst_C = [4,4,5,6,6]
        lst_H = [9,10,11,13,12]
        for FG2xyz in functionalGroups:
            FG2 = FG2xyz[:-4]
            for i,pos2 in enumerate(lst_pos2):
                outfile = str(pos1) + "_" + str(FG1) + "_" + str(pos2) + "_" + str(FG2) + ".xyz"
                exchangeAtom(lst_C[i],lst_H[i],filename,pathCoords + FG2xyz,outfile)

    if pos1 == "4.1":
        lst_pos2 = ["4.2","5","6.2","6.1"]
        lst_C = [4,5,6,6]
        lst_H = [10,11,13,12]
        for FG2xyz in functionalGroups:
            FG2 = FG2xyz[:-4]
            for i,pos2 in enumerate(lst_pos2):
                outfile = str(pos1) + "_" + str(FG1) + "_" + str(pos2) + "_" + str(FG2) + ".xyz"
                exchangeAtom(lst_C[i],lst_H[i],filename,pathCoords + FG2xyz,outfile)

    if pos1 == "4.2":
        lst_pos2 = ["5","6.2","6.1"]
        lst_C = [5,6,6]
        lst_H = [11,13,12]
        for FG2xyz in functionalGroups:
            FG2 = FG2xyz[:-4]
            for i,pos2 in enumerate(lst_pos2):
                outfile = str(pos1) + "_" + str(FG1) + "_" + str(pos2) + "_" + str(FG2) + ".xyz"
                exchangeAtom(lst_C[i],lst_H[i],filename,pathCoords + FG2xyz,outfile)

    if pos1 == "5":
        lst_pos2 = ["6.2","6.1"]
        lst_C = [6,6]
        lst_H = [13,12]
        for FG2xyz in functionalGroups:
            FG2 = FG2xyz[:-4]
            for i,pos2 in enumerate(lst_pos2):
                outfile = str(pos1) + "_" + str(FG1) + "_" + str(pos2) + "_" + str(FG2) + ".xyz"
                exchangeAtom(lst_C[i],lst_H[i],filename,pathCoords + FG2xyz,outfile)

    if pos1 == "6.1":
        lst_pos2 = ["6.2"]
        lst_C = [6]
        lst_H = [13]
        for FG2xyz in functionalGroups:
            FG2 = FG2xyz[:-4]
            for i,pos2 in enumerate(lst_pos2):
                outfile = str(pos1) + "_" + str(FG1) + "_" + str(pos2) + "_" + str(FG2) + ".xyz"
                exchangeAtom(lst_C[i],lst_H[i],filename,pathCoords + FG2xyz,outfile)

