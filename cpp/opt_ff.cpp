#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <random>

#include <openbabel/base.h>
#include <openbabel/forcefield.h>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/atom.h>
#include <openbabel/babelconfig.h>
#include <openbabel/builder.h>
#include <openbabel/math/vector3.h>

int main(int argc, char *argv[]) {

OpenBabel::OBMol mol;
OpenBabel::OBAtom *atom;
OpenBabel::OBConversion conv;
conv.SetInAndOutFormats("xyz","xyz");

std::string filename = argv[1];
std::string outfile = filename.substr(0, filename.size()-4);

outfile += "_2.xyz";

std::ofstream ofs(outfile);

std::ifstream ifs;
ifs.open(filename.c_str());
conv.Read(&mol, &ifs);
ifs.close();

OpenBabel::OBForceField* pFF = OpenBabel::OBForceField::FindForceField("UFF");

OpenBabel::OBFFConstraints constraints;
for (int a=1; a <= 5; a++) {
  atom = mol.GetAtom(a);
  //std::cout << atom << std::endl;
  constraints.AddAtomConstraint(atom->GetIdx());
}

//pFF->Setup(mol, constraints);

if (!pFF->Setup(mol, constraints)) {
      std::cerr << "ERROR: could not setup force field." << std::endl;
      }

//std::cout << "energy: " << pFF->Energy() << std::endl;

pFF->ConjugateGradients(1000);

pFF->UpdateCoordinates(mol);

//std::cout << "energy: " << pFF->Energy() << std::endl;

conv.Write(&mol, &ofs);

}
