use std::fs::File;
use std::io::{BufRead, BufReader};
use std::error::Error;
use crate::molecule::Molecule;

/// Load molecules from a MOL2 file
pub fn load_from_mol2(filename: &str) -> Result<Vec<Molecule>, Box<dyn Error>> {
    let file = File::open(filename)?;
    let reader = BufReader::new(file);

    let mut molecules = Vec::new();
    let mut current = Molecule::new();

    let mut in_atom_section = false;
    let mut in_bond_section = false;

    for line in reader.lines() {
        let line = line?;

        if line.contains("@<TRIPOS>MOLECULE") {
            if !current.empty() {
                molecules.push(current);
                current = Molecule::new();
            }
            in_atom_section = false;
            in_bond_section = false;
        } else if line.contains("@<TRIPOS>ATOM") {
            in_atom_section = true;
            in_bond_section = false;
            continue;
        } else if line.contains("@<TRIPOS>BOND") {
            in_atom_section = false;
            in_bond_section = true;
            continue;
        } else if line.starts_with('@') {
            in_atom_section = false;
            in_bond_section = false;
            continue;
        }

        if in_atom_section {
            let parts: Vec<&str> = line.split_whitespace().collect();
            if parts.len() >= 6 {
                let element = parts[1];
                let x: f64 = parts[2].parse()?;
                let y: f64 = parts[3].parse()?;
                let z: f64 = parts[4].parse()?;
                current.add_atom(element, x, y, z);
            }
        } else if in_bond_section {
            let parts: Vec<&str> = line.split_whitespace().collect();
            if parts.len() >= 4 {
                let a1: usize = parts[1].parse()?; // mol2 atoms are 1-based
                let a2: usize = parts[2].parse()?;
                let order_str = parts[3];

                let order = match order_str {
                    "2" => 2,
                    "3" => 3,
                    "ar" => 1,
                    _ => 1,
                };

                current.add_bond(a1 - 1, a2 - 1, order); // convert to 0-based
            }
        }
    }

    if !current.empty() {
        molecules.push(current);
    }

    Ok(molecules)
}
