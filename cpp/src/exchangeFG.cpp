#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>
#include <boost/tokenizer.hpp>

#include <openbabel/base.h>
#include <openbabel/forcefield.h>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/atom.h>
#include <openbabel/babelconfig.h>
#include <openbabel/builder.h>
#include <openbabel/math/vector3.h>
#include <openbabel/obiter.h>
#include <openbabel/obutil.h>

#include "func.hpp"
#include "utils.hpp"


int main(int argc, char *argv[])
{
	// check # of cmd line argumentas
	if( argc < 6 ) {
		std::cout << "\033[1;31m cmd line should look like: ./main <file_in> <file_out> <position> <FG to delete> <FG to add> \033[1;0m" << std::endl;
		return 1;
	}

	// cmd line arguments
	std::string file_in = argv[1];
	std::string file_out = argv[2];
  int position = atoi(argv[3]);
	std::string toDelete = argv[4];
	std::string fgE = argv[5];

	// declare variables
	int C;
	int Idx_to_connect;
	std::vector<int> to_delete;

	// get number of C atom to exchange the FG
	std::string base_in = file_in.substr(0, file_in.size()-4);
	if( (position == 1) || (position == 2) ) {
		C = 1;
	} else {
		C = 2;
	}

	// declare OpenBabel variables 
	OpenBabel::OBMol mol, FG;
	OpenBabel::vector3 vec;
	OpenBabel::OBBuilder build;
	OpenBabel::OBConversion convMol, convFG;
	convMol.SetInAndOutFormats("xyz","xyz");
	convFG.SetInAndOutFormats("xyz","xyz");

	// read in molecule 
	std::ifstream ifs_mol;
	ifs_mol.open(file_in.c_str());
	convMol.Read(&mol, &ifs_mol);
	ifs_mol.close();

	// read in FG
	std::ifstream ifs_fg;
	ifs_fg.open(fgE.c_str());
	convFG.Read(&FG, &ifs_fg);
	ifs_fg.close();

	// output stream
	std::ofstream ofs(file_out);

	// get vector contianing idx's of atoms to delete
	if(toDelete == "A") {
		to_delete = get_H(C, mol);
	} else if (toDelete == "B") {
		to_delete = get_NO2(C, mol);
	} else if (toDelete == "C") {
		to_delete = get_CN(C, mol);
	} else if (toDelete == "D") {
		to_delete = get_CH3(C, mol);
	} else {
		to_delete = get_NH2(C, mol);
	}

	// delete FG
	mol = delete_FG(to_delete, mol);

	// get Idx of last atom
	Idx_to_connect = mol.NumAtoms();

	// add new FG
	mol += FG;
	build.Connect(mol, C, Idx_to_connect + 1, 1);

	// optimize new FG with UFF 
	mol = opt_ff(mol);

	// write xyz file of new molecule
	convMol.Write(&mol, &ofs);

}

