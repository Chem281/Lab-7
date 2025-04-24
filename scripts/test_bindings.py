import sys
import os

project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# Append 'build' folder from project root
sys.path.append(os.path.join(project_root, 'build'))

import mol

def main():
    mols = mol.load_from_mol2("../files/mols.mol2")
    print(len(mols))
    filtered_mols = mol.filter_molecules(mols)
    print(len(filtered_mols))

if __name__ == "__main__":
    main()