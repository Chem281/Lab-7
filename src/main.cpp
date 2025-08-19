#include "molecule.h"
#include <chrono>
#include <iostream>

int main() {
    // Load the molecules
    std::vector<Molecule> mols = load_from_mol2("../files/mols.mol2");
    std::cout << mols.size() << std::endl;
    std::cout << mols[0].get_atoms().size() << std::endl;
    std::cout << mols[0].get_atoms()[24].element << std::endl;
    std::cout << mols[0].get_atoms()[24].x << std::endl;
    std::cout << mols[0].get_atoms()[24].y << std::endl;
    std::cout << mols[0].get_atoms()[24].z << std::endl;

    // Using filter_molecules_wrapper
    auto filtered_mols = filter_molecules(mols);
    std::cout << "Filtered mols: " << filtered_mols.size() << std::endl;
}
