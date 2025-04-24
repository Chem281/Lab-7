#include "molecule.h"

#include "element_utils.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <omp.h>

Molecule::AtomID Molecule::add_atom(const std::string& element, double x, double y, double z) {
    int atomic_number = get_atomic_number(element);
    atoms.push_back({num_atoms, element, atomic_number, x, y, z});
    adjacency[num_atoms] = {};
    return num_atoms++;
}

void Molecule::add_bond(AtomID a1, AtomID a2, int order) {
    bonds.push_back({a1, a2, order});
    adjacency[a1].push_back(a2);
    adjacency[a2].push_back(a1);
}

const std::vector<Molecule::Atom>& Molecule::get_atoms() const {
    return atoms;
}

const std::vector<Molecule::Bond>& Molecule::get_bonds() const {
    return bonds;
}

std::vector<Molecule::AtomID> Molecule::neighbors(AtomID id) const {
    auto it = adjacency.find(id);
    if (it != adjacency.end()) {
        return it->second;
    }
    return {};
}

bool Molecule::empty() const {
    return atoms.empty();
}

std::vector<Molecule> load_from_mol2(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        throw std::runtime_error("File not found");
    }

    std::vector<Molecule> molecules;
    Molecule current;

    std::string line;
    bool in_atom_section = false;
    bool in_bond_section = false;

    while (std::getline(infile, line)) {
        if (line.find("@<TRIPOS>MOLECULE") != std::string::npos) {
            if (!current.empty()) {
                molecules.push_back(current);
                current = Molecule();  // Start fresh
            }
            in_atom_section = in_bond_section = false;
        } else if (line.find("@<TRIPOS>ATOM") != std::string::npos) {
            in_atom_section = true;
            in_bond_section = false;
            continue;
        } else if (line.find("@<TRIPOS>BOND") != std::string::npos) {
            in_atom_section = false;
            in_bond_section = true;
            continue;
        } else if (line.size() && line[0] == '@') {
            in_atom_section = in_bond_section = false;
            continue;
        }

        if (in_atom_section) {
            std::istringstream ss(line);
            int id;
            std::string name, element;
            double x, y, z;
            ss >> id >> name >> x >> y >> z >> element;
            current.add_atom(element, x, y, z);
        } else if (in_bond_section) {
            std::istringstream ss(line);
            int bond_id, a1, a2;
            std::string order_str;
            ss >> bond_id >> a1 >> a2 >> order_str;

            int order = 1;
            if (order_str == "2") order = 2;
            else if (order_str == "3") order = 3;
            else if (order_str == "ar") order = 1; // aromatic

            current.add_bond(a1 - 1, a2 - 1, order);
        }
    }

    // Add the last molecule if it had content
    if (!current.empty()) {
        molecules.push_back(current);
    }

    return molecules;
}

std::vector<std::vector<double>> geometric_centroid(const std::vector<Molecule>& mols)
{
    // Calculate the geometric cetroind for each molecule in mols.
}

std::vector<Molecule> filter_molecules(const std::vector<Molecule>& mols)
{
    // Apply 2 filters to the list of molecules:
    // 1. Only molecules with atoms <= 25 are allowed.
    // 2. Only molecules with ALL single bonds are allowed.
}
