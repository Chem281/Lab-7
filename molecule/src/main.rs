mod molecule;
mod loadmols;

use molecule::Molecule;
use loadmols::load_from_mol2;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let molecules = load_from_mol2("../files/mols.mol2")?;
    println!("Loaded {} molecule(s)", molecules.len());
    let small_molecules: Vec<&Molecule> = molecules.iter().filter(|m| m.get_atoms().len() <= 25).collect();
    println!("{} small molecule(s)", small_molecules.len());
    let hbond_donors: Vec<&Molecule> = molecules.iter().filter(|m| m.count_hbond_donors() > 1).collect();
    println!("{} hbd molecule(s)", hbond_donors.len());
    let hbond_acceptors: Vec<&Molecule> = molecules.iter().filter(|m| m.count_hbond_acceptors() > 1).collect();
    println!("{} hba molecule(s)", hbond_acceptors.len());
    Ok(())
}