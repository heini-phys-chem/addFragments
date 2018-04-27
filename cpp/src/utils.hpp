#ifndef SRC_UTILS_HPP
#define SRC_UTILS_HPP
#define HAVE_EIGEN

OpenBabel::OBMol opt_ff(OpenBabel::OBMol mol) {
	OpenBabel::OBForceField* pFF = OpenBabel::OBForceField::FindForceField("UFF");
	OpenBabel::OBFFConstraints constraints;
	int numAtoms = mol.NumAtoms();

	std::cout << std::endl;
	for(int i=1; i <= numAtoms-3; i++) {
		std::cout << i << std::endl;
		constraints.AddAtomConstraint(i);
	}

	pFF->SetConstraints(constraints);

	if (!pFF->Setup(mol, constraints)) {
		std::cerr << "ERROR: could not setup force field." << std::endl;
	}

	//std::cout << "energy: " << pFF->Energy() << std::endl;
	pFF->ConjugateGradients(1000);
	pFF->UpdateCoordinates(mol);


	return mol;	

}

OpenBabel::OBMol delete_FG(std::vector<int> to_delete, OpenBabel::OBMol mol) {
	// print statements to test loops
	std::cout << "\033[1;31m\nrandom order (from OB)\033[1;0m" << std::endl;
	for( int n : to_delete ) {
		std::cout << n << std::endl;
	}
	std::sort(to_delete.rbegin(), to_delete.rend());
	std::cout << "\033[1;31m\nreversed order\033[1;0m" << std::endl;
	for( int n : to_delete ) {
		std::cout << n << std::endl;
	}

	// delete old FG
	for(int i = 0; (unsigned) i < to_delete.size(); i++) {
		mol.DeleteAtom(mol.GetAtom(to_delete[i]));
	}

	return mol; 

}

// get CH3
std::vector<int> get_CH3(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
	std::cout << "\033[1;31m\nAtom Idx's of Functional Group\033[1;0m" << std::endl;
  FOR_NBORS_OF_ATOM(nbr, atom) {
		if ( (nbr->GetIdx()) == 1 || (nbr->GetIdx() == 2) ) {
			continue;
		}
		if ( (mol.GetAtom(nbr->GetIdx()))->IsCarbon() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());
			vec.push_back(nbr->GetIdx());
			std::cout << "atom #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
		} else {
			continue;
			}

		// ionner loop over second neighbouring atoms
		FOR_NBORS_OF_ATOM(nbr2, atom2) {
			if ( (nbr2->GetIdx()) == 1 || (nbr2->GetIdx() == 2) ) {
			continue;
			}
			if ( (mol.GetAtom(nbr2->GetIdx()))->IsHydrogen() ) {
				vec.push_back(nbr2->GetIdx());
				std::cout << "atom #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
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
	std::cout << "\033[1;31m\nAtom Idx's of Functional Group\033[1;0m" << std::endl;
  FOR_NBORS_OF_ATOM(nbr, atom) {
		if ( (nbr->GetIdx()) == 1 || (nbr->GetIdx() == 2) ) {
			continue;
		}
		if ( (mol.GetAtom(nbr->GetIdx()))->IsHydrogen() ) {
			vec.push_back(nbr->GetIdx());
			std::cout << "atom #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
		} else {
			continue;
			}
	}

	return vec;
}

// get NO2 
std::vector<int> get_NO2(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
	std::cout << "\033[1;31m\nAtom Idx's of Functional Group\033[1;0m" << std::endl;
  FOR_NBORS_OF_ATOM(nbr, atom) {
		if ( (nbr->GetIdx()) == 1 || (nbr->GetIdx() == 2) ) {
			continue;
		}
		if ( (mol.GetAtom(nbr->GetIdx()))->IsNitrogen() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());
			vec.push_back(nbr->GetIdx());
			std::cout << "atom #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
		} else {
			continue;
			}

		// ionner loop over second neighbouring atoms
		FOR_NBORS_OF_ATOM(nbr2, atom2) {
			if ( (nbr2->GetIdx()) == 1 || (nbr2->GetIdx() == 2) ) {
			continue;
			}
			if ( (mol.GetAtom(nbr2->GetIdx()))->IsOxygen() ) {
				vec.push_back(nbr2->GetIdx());
				std::cout << "atom #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
			}
		}
	}

	return vec;
}

// get CN 
std::vector<int> get_CN(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
	std::cout << "\033[1;31m\nAtom Idx's of Functional Group\033[1;0m" << std::endl;
  FOR_NBORS_OF_ATOM(nbr, atom) {
		if ( (nbr->GetIdx()) == 1 || (nbr->GetIdx() == 2) ) {
			continue;
		}
		if ( (mol.GetAtom(nbr->GetIdx()))->IsCarbon() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());
			vec.push_back(nbr->GetIdx());
			std::cout << "atom #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
		} else {
			continue;
			}

		// ionner loop over second neighbouring atoms
		FOR_NBORS_OF_ATOM(nbr2, atom2) {
			if ( (nbr2->GetIdx()) == 1 || (nbr2->GetIdx() == 2) ) {
			continue;
			}
			if ( (mol.GetAtom(nbr2->GetIdx()))->IsNitrogen() ) {
				vec.push_back(nbr2->GetIdx());
				std::cout << "atom #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
			}
		}
	}

	return vec;
}

// get NH2 
std::vector<int> get_NH2(int C, OpenBabel::OBMol mol) {
	std::vector<int> vec;
	OpenBabel::OBAtom *atom, *atom2;

	atom = mol.GetAtom(C);

	// outer loop over first neighbouring atoms
	std::cout << "\033[1;31m\nAtom Idx's of Functional Group\033[1;0m" << std::endl;
  FOR_NBORS_OF_ATOM(nbr, atom) {
		if ( (nbr->GetIdx()) == 1 || (nbr->GetIdx() == 2) ) {
			continue;
		}
		if ( (mol.GetAtom(nbr->GetIdx()))->IsNitrogen() ) {
			atom2 = mol.GetAtom(nbr->GetIdx());
			vec.push_back(nbr->GetIdx());
			std::cout << "atom #" << atom->GetIdx() << " is bound to atom #" << nbr->GetIdx() << std::endl;
		} else {
			continue;
			}

		// ionner loop over second neighbouring atoms
		FOR_NBORS_OF_ATOM(nbr2, atom2) {
			if ( (nbr2->GetIdx()) == 1 || (nbr2->GetIdx() == 2) ) {
			continue;
			}
			if ( (mol.GetAtom(nbr2->GetIdx()))->IsHydrogen() ) {
				vec.push_back(nbr2->GetIdx());
				std::cout << "atom #" << atom2->GetIdx() << " is bound to atom #" << nbr2->GetIdx() << std::endl;
			}
		}
	}

	return vec;
}

std::string *get_labels(std::string base_in, char delim) {
// function that returns an array of the labels in the file name
	int j = 0;
	std::string *arr = new std::string[5];

	for( int i = 0; i < 5; i++) {
		if(base_in[i] == delim) {
			j++;
			continue;
		}
		arr[j] += base_in[i];
	}
	return arr;
}

#endif
