import sys
import glob
import re
import openbabel as ob

def opt_mmff_FG(mol, numAtoms, outfile):
    # initialize force field and constraint classes
    MMFF = ob.OBForceField.FindType("UFF")
    constraints = ob.OBFFConstraints()
    conv = ob.OBConversion()
    conv.SetInAndOutFormats("xyz","xyz")

    # setup force field
    MMFF.Setup(mol)

    end = mol.NumAtoms()

    # add constraints
    [constraints.AddAtomConstraint(i) for i in range(1,numAtoms)]
    [constraints.AddAtomConstraint(i) for i in range(numAtoms+1,end)]
    MMFF.SetConstraints(constraints)

    # run optization 
    MMFF.ConjugateGradients(1000)

    # update coordinates
    MMFF.UpdateCoordinates(mol)

    # write to xyz file
    print outfile
    conv.WriteFile(mol, "out_xyz/" + outfile)

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
    #convTS.WriteFile(TS, "out_xyz/" + outfile)

    # clear TS and FG molecule classes
    TS.Clear()
    FG.Clear()

if __name__ == "__main__":

    filename = sys.argv[1]
    pathCoords = "/home/stefan/PhD/projects/reactions/claisen/data_set_new_FG/xyz/coords_new/"
    functionalGroups = ["BOH2.xyz", "Br.xyz", "CC_DB.xyz", "CC_TB.xyz", "Cl.xyz", "COCl.xyz", "CONH2.xyz", "COOCH3.xyz", "COSH.xyz", "COSMe.xyz", "CSOH.xyz", "F.xyz", "MgCl.xyz", "N2.xyz", "N3.xyz", "NHNH2.xyz", "OCOCH3.xyz", "OH.xyz", "OMe.xyz", "ONH2.xyz", "PH2.xyz", "SH.xyz", "SiME3.xyz", "NH2.xyz", "NO2.xyz", "CN.xyz"]
    positions = ["2.1", "2.2", "3", "4.1", "4.2", "5", "6.1", "6.2"]
    H = [7,8,9,10,11,12,13,14]
    C = [2,2,3,4,4,5,6,6]

    for functionalGroup in functionalGroups:
      for i,position in enumerate(positions):
        outfile = position + "_" + functionalGroup[:-4] + ".xyz"
        fg = str(pathCoords) + str(functionalGroup)
        exchangeAtom(C[i], H[i], filename, fg, outfile)
'''
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

'''
