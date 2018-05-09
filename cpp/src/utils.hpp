#ifndef SRC_UTILS_HPP
#define SRC_UTILS_HPP
#define HAVE_EIGEN

OpenBabel::OBMol opt_ff(OpenBabel::OBMol mol, int numAtomFG, OpenBabel::vector3 vec) {
/* optimize only the new FG in OBMol with the UFF force field */
	OpenBabel::OBForceField* pFF = OpenBabel::OBForceField::FindForceField("UFF");
	OpenBabel::OBFFConstraints constraints;
	int numAtoms = mol.NumAtoms();

	for(int i=0; i < numAtoms - numAtomFG - 1; i++) {
		constraints.AddAtomConstraint(i);
	}

	pFF->SetConstraints(constraints);

	if (!pFF->Setup(mol, constraints)) {
		std::cerr << "ERROR: could not setup force field." << std::endl;
	}

	pFF->ConjugateGradients(1000);
	pFF->UpdateCoordinates(mol);

	return mol;	
}

OpenBabel::OBMol delete_FG(std::vector<int> to_delete, OpenBabel::OBMol mol) {
/* Function to delete the atoms (stored in a vector<int>) in OBMol */
	std::sort(to_delete.rbegin(), to_delete.rend());
	for(int i = 0; (unsigned) i < to_delete.size(); i++) {
		mol.DeleteAtom(mol.GetAtom(to_delete[i]));
	}
	return mol; 
}

// get CH3
std::vector<int> get_CH3(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;
	int counter;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
  FOR_NBORS_OF_ATOM(nbr, atom) {
		counter = 0;
		if(nbr->GetIdx() == 1) continue;
		if(nbr->GetIdx() == 2) continue;

		if ( (mol.GetAtom(nbr->GetIdx()))->IsCarbon() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());

			// inner loop over second neighbours
			FOR_NBORS_OF_ATOM(nbr2, atom2) {
				if(nbr2->GetIdx() == 1) continue;
				if(nbr2->GetIdx() == 2) continue;

				if ( (mol.GetAtom(nbr2->GetIdx()))->IsHydrogen() ) {
					vec.push_back(nbr2->GetIdx());
					std::cout << "atom2 #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
					counter++;
				}
			}
			if( counter == 3) { 	
				vec.push_back(nbr->GetIdx());
				std::cout << "atom1 #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
			}
		}
	}
	return vec;
}

// get H
std::vector<int> get_H(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
  FOR_NBORS_OF_ATOM(nbr, atom) {
		if(nbr->GetIdx() == 1) continue;
		if(nbr->GetIdx() == 2) continue;
		if(nbr->GetIdx() == 5) continue;
		if ( (mol.GetAtom(nbr->GetIdx()))->IsHydrogen() ) {
			vec.push_back(nbr->GetIdx());
			std::cout << "atomH #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
		}
	}
	return vec;
}

// get NO2 
std::vector<int> get_NO2(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;
	int counter;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
  FOR_NBORS_OF_ATOM(nbr, atom) {
		counter = 0;
		if(nbr->GetIdx() == 1) continue;
		if(nbr->GetIdx() == 2) continue;

		if ( (mol.GetAtom(nbr->GetIdx()))->IsNitrogen() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());

			// inner loop over second neighbours
			FOR_NBORS_OF_ATOM(nbr2, atom2) {
				if(nbr2->GetIdx() == 1) continue;
				if(nbr2->GetIdx() == 2) continue;

				if ( (mol.GetAtom(nbr2->GetIdx()))->IsOxygen() ) {
					vec.push_back(nbr2->GetIdx());
					std::cout << "atom2 #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
					counter++;
				}
			}
			if( counter == 2) { 	
				vec.push_back(nbr->GetIdx());
				std::cout << "atom1 #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
			}
		}
	}
	return vec;
}

// get CN 
std::vector<int> get_CN(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;
	int counter;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
  FOR_NBORS_OF_ATOM(nbr, atom) {
		counter = 0;
		if(nbr->GetIdx() == 1) continue;
		if(nbr->GetIdx() == 2) continue;

		if ( (mol.GetAtom(nbr->GetIdx()))->IsCarbon() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());

			// inner loop over second neighbours
			FOR_NBORS_OF_ATOM(nbr2, atom2) {
				if(nbr2->GetIdx() == 1) continue;
				if(nbr2->GetIdx() == 2) continue;

				if ( (mol.GetAtom(nbr2->GetIdx()))->IsNitrogen() ) {
					vec.push_back(nbr2->GetIdx());
					std::cout << "atom2 #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
					counter++;
				}
			}
			if( counter == 1) { 	
				vec.push_back(nbr->GetIdx());
				std::cout << "atom1 #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
			}
		}
	}
	return vec;
}

// get NH2 
std::vector<int> get_NH2(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;
	int counter;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
  FOR_NBORS_OF_ATOM(nbr, atom) {
		counter = 0;
		if(nbr->GetIdx() == 1) continue;
		if(nbr->GetIdx() == 2) continue;

		if ( (mol.GetAtom(nbr->GetIdx()))->IsNitrogen() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());

			// inner loop over second neighbours
			FOR_NBORS_OF_ATOM(nbr2, atom2) {
				if(nbr2->GetIdx() == 1) continue;
				if(nbr2->GetIdx() == 2) continue;

				if ( (mol.GetAtom(nbr2->GetIdx()))->IsHydrogen() ) {
					vec.push_back(nbr2->GetIdx());
					std::cout << "atom2 #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
					counter++;
				}
			}
			if( counter == 2) { 	
				vec.push_back(nbr->GetIdx());
				std::cout << "atom1 #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
			}
		}
	}
	return vec;
}

OpenBabel::vector3 get_vector(std::vector<int> to_delete, OpenBabel::OBMol mol, int C) {
/* get the vector of the attached OBAtom */
	OpenBabel::vector3 vec;
	int Idx;
	double X, Y, Z;

	std::sort(to_delete.begin(), to_delete.end());

	std::cout << "to_delete[0] = " << to_delete[0]	<< std::endl;
	Idx = to_delete[0];

	X = mol.GetAtom(Idx)->GetX();
	Y = mol.GetAtom(Idx)->GetY();
	Z = mol.GetAtom(Idx)->GetY();

	vec.Set(X,Y,Z);


	return vec;
}

std::vector<std::string> get_R(std::string file) {
/* get the labels of the FG's */
	std::vector<std::string> vec;
	
	for ( unsigned i=0; i<7; i++ ) { 
  	if ( file.substr(5,7)[i] == '_' ) {
    	continue;
  	} else {
    	vec.push_back(file.substr(5,7).substr(i, 1));
  	}
	}
	return vec;
}

#endif
