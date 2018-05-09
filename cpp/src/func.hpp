#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>

OpenBabel::OBMol opt_ff(OpenBabel::OBMol mol);

OpenBabel::OBMol delete_FG(std::vector<int> to_delete, OpenBabel::OBMol mol);

OpenBabel::vector3 get_vector(std::vector<int> to_delete, OpenBabel::OBMol mol);

std::vector<int> get_CH3(int C, OpenBabel::OBMol mol);

std::vector<int> get_H(int C, OpenBabel::OBMol mol);

std::vector<int> get_NO2(int C, OpenBabel::OBMol mol);

std::vector<int> get_CN(int C, OpenBabel::OBMol mol);

std::vector<int> get_NH2(int C, OpenBabel::OBMol mol);

std::vector<std::string> get_R(std::string file); 

