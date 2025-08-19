# 💻 CHEM 281 Lab 7: Molecules, Templates, Lambdas, Rust

## 🧪 Goal

The goal of this lab is to:

1. Familiarize yourself with **representing chemical structures** in a computer.
2. Practice using **C++ templates** and **lambdas**.
3. Learn how to write and compile **Rust code**.
4. Work with **3D molecular coordinates** generated from SMILES strings.

---

## 🗂️ Provided

- Starter code in C++ and Rust to read and store molecules.
- Helper functions
- Docker environment with rdkit.
- Python script to create mol files: `scripts/smi_to_mol.py`

---

## 💻 Setup
```bash
./build_image.sh # You may need to chmod +x
./interactive.sh 
```

## ✅ Tasks

### 1. **Generate a `.mol2` file**

Use the provided script to generate `.mol` files:

```bash
python scripts/smi_to_mol.py
```

Then once its made you should have a new directory with all the .mol files `files/mols`. You need to then use openbabel to convert all the mol files into a single .mol2 file. If you change the name of any of these files then the executable based on main.cpp won't be able to find it so you can just update the names then.

```bash
obabel -imol files/mols/*.mol -O files/mols.mol2
```

### 2. **Complete the C++ functions**
`filter_molecules`
You should apply 2 filters to the list of molecules to trim their size down from 80.
    1. Only molecules with atoms <= 25 are allowed.
    2. Only molecules with ALL single bonds are allowed.
    3. Only molecules with more than 1 HBA and 1 HBD are allowed.

These filters are excluding molecules that are too large (lets pretend our active site is really small!), and contains molecules that have a lot of degrees of freedom.

`countHBondDonors`
A HBond donor for our purposes is an Oxygen or Nitrogen atom with a full valency with atleast 1 hydrogen attached. The way we would look for them is by checking if the total bond order of an Oxygen is 2 and it has 1 hydrogen as a neighbor. For Nitrogens the total bond order would be 3 and it has 1 hydrogen as a neighbor.

`countHBondAcceptors`
A HBond acceptor for our purposes is an Oxygen or Nitrogen atom with a full valency. The way we would look for them is by checking if the total bond order of an Oxygen is 2. For Nitrogens the total bond order would be 3.

Note: A double bonded Oxygen has a bond order of 2.
Note: An atom can be considered both an acceptor and a donor. Example: Water oxygen.

Build and run the executable `./mol_exe` from the build.
```bash
mkdir build
cd build
make
./mol_exe
```
### 3. **Complete the Rust functions**
Complete `count_hbond_acceptors` and `count_hbond_donors` in `molecule.rs`. They are identical to the C++ functions just written in Rust! Once completed, filter the molecules but instead of using an explicit `filter_molecules` function, chain iterators together to to achieve the same functionality.

Build and run:
```bash
cd molecule
cargo run
```

### Extra time
Spend some time looking at the differences and similarities between the C++ code and the Rust code. You can also look at the `smi_to_mol.py` script which was used to generate 3D structures from SMILES.
