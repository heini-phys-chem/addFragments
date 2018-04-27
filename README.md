# addFragments
This is a python script that adds chemical fragments (XYZ coordinates) to a target molecule (XYZ coordinates) using python and OpenBabel

hard coded for a special cases (addFG.py for claisen and addFG_sn_e.py for elimination and substitution reactions) and also for specific file names...

The Force filed selected as default is MMFF94. This does not have parameters for every atom and if it fails, there will be no error message (http://openbabel.org/dev-api/classOpenBabel_1_1OBForceField.shtml)

The cpp directory contains a script to exchange functional groups with other functional groups
