#include <stdio.h>
#include <stdlib.h>
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
	if( argc < 2 ) {
		std::cout << "\033[1;31m cmd line should look like: ./main <file_in> <file_out> <position> <FG to delete> <FG to add> \033[1;0m" << std::endl;
		return 1;
	}

	//std::cout << "\033[1;31m start new molecule \033[1;0m" << std::endl;

	// cmd line arguments
	std::string file_in = argv[1];
	std::string file_out = argv[2];
	std::string rxn = argv[3];

	// declare OpenBabel variables 
	OpenBabel::OBMol mol, FG;
	OpenBabel::vector3 vec;
	OpenBabel::OBBuilder build;
	OpenBabel::OBConversion convMol, convFG;
	convMol.SetInAndOutFormats("xyz","xyz");
	convFG.SetInAndOutFormats("xyz","xyz");

	// declare variables
	int C;
	int numAtomFG;
	int Idx_to_connect;
  int position = 0;
	std::vector<int> to_delete;
	std::string toDelete;
	std::string fgE;
	std::vector<std::string> in;
	std::vector<std::string> out;

	// get input variables
	in = get_R(file_in);
	out = get_R(file_out);

	// compare R1-R4 (strin in vs string out)
	for( int i=0; i < 4; i++) {
		if( in[i] == out[i] ) {
			continue;
		} else {
			toDelete = in[i];
			fgE = out[i];
			position = i+1;
		}
	}

	std::string out_file_name = "inp.xyz";
/*
	out_file_name.append("inp.xyz");
  out_file_name.insert(0,"xyz_out/");
	out_file_name.append("-");
	out_file_name.append(file_out);
	out_file_name.append(".xyz");
*/

	// some fancy print statements

/*
	std::cout << file_in.substr(5,7) << std::endl;
	std::cout << file_out.substr(5,7) << std::endl;

	std::cout << "\nposition: " << position << std::endl;
	std::cout << "\ntoDelete: " << toDelete << std::endl;
	std::cout << "\nfgE: " << fgE << std::endl;
	std::cout << "\nout_file: : " << out_file_name << std::endl;
*/

	// get Idx of C atom to exchange the FG
	std::string base_in = file_in.substr(0, file_in.size()-4);
	if( (position == 1) || (position == 2) ) {
		C = 1;
		if( in[0] == in[1] ) std::exit(EXIT_FAILURE);
	} else {
		C = 2;
		if( in[2] == in[3] ) std::exit(EXIT_FAILURE);
	}

	// read in molecule 
	file_in.insert(0,rxn);
	file_in.append(".xyz");
	std::ifstream ifs_mol;
	ifs_mol.open(file_in.c_str());
	convMol.Read(&mol, &ifs_mol);
	ifs_mol.close();

	// read in FG
	fgE.append(".xyz");
	fgE.insert(0,"xyz/");
	std::ifstream ifs_fg;
	ifs_fg.open(fgE.c_str());
	convFG.Read(&FG, &ifs_fg);
	ifs_fg.close();

	// output streams
	std::ofstream ofs(out_file_name);

	// get cpp vector contianing idx's of atoms to delete
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

	// get vector3 of position of FG
	vec = get_vector(to_delete, mol, C);

	// delete FG
	mol = delete_FG(to_delete, mol);

	// get Idx of last atom
	Idx_to_connect = mol.NumAtoms();

	// add new FG
	mol += FG;
	build.Connect(mol, C, Idx_to_connect + 1, vec, 1);

	// optimize new FG with UFF 
	numAtomFG = FG.NumAtoms();
	mol = opt_ff(mol, numAtomFG, vec);

	// write xyz file of new molecule
	convMol.Write(&mol, &ofs);

}

