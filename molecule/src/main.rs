mod molecule;
mod loadmols;

use molecule::Molecule;
use loadmols::load_from_mol2;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let molecules = load_from_mol2("../files/mols.mol2")?;
    println!("Loaded {} molecule(s)", molecules.len());
    Ok(())
}
