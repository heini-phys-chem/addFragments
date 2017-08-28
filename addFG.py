import sys
import glob
import re
import openbabel as ob

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

    # write new molecule to file
    convTS.WriteFile(TS, "out/" + outfile)

    # clear TS and FG molecule classes
    TS.Clear()
    FG.Clear()

if __name__ == "__main__":

    filenames = glob.glob("./*.xyz")
    pathCoords = "/home/stefan/PhD/projects/claisen/data_set/coords/"
    functionalGroup = ["br.xyz","cbr3.xyz","ccl3.xyz","cf3.xyz","ch3.xyz","cl.xyz","cn.xyz","cocbr3.xyz","coccl3.xyz","cocf3.xyz","coh.xyz","cooh.xyz","f.xyz","nh2.xyz","no2.xyz","och3.xyz","oh.xyz","ph.xyz"]

    dic21 = {'2.2':[7], '3':[8], '4.1':[9], '4.2':[10], '5':[11], '6.1':[12], '6.2':[13]}
    #dic22 = {'3':[8], '4.1':[9], '4.2':[10], '5':[11], '6.1':[12], '6.2':[13]}
    #dic3 = {'4.1':[9], '4.2':[10], '5':[11], '6.1':[12], '6.2':[13]}
    #dic41 = {'4.2':[10], '5':[11], '6.1':[12], '6.2':[13]}
    #dic42 = {'5':[11], '6.1':[12], '6.2':[13]}
    #dic5 = {'6.1':[12], '6.2':[13]}
    #dic61 = {'6.2':[13]}

    for filename in filenames:
        pos1 = filename.split('_')[0]
        print "pos1: " + str(pos1)
        FG1 = (filename.split('_')[1])[:-4]
        print "FG1: " + str(FG1)

        for keys, values in dic21.items():
            pos2 = str(keys)
            for val in values:
                for fg in functionalGroup:
                    FG2 = str(fg[:-4])
                    outfile = pos1 + "_" + FG1 + "_" + pos2 + "_" + FG2 + ".xyz"
                    exchangeAtom(int(keys[0]), int(val), filename, pathCoords + fg ,outfile)

