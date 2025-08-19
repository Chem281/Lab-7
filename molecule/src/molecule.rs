use std::collections::HashMap;

type AtomID = usize;

#[derive(Debug, Clone)]
pub struct Atom {
    pub id: AtomID,
    pub element: String,
    pub atomic_number: i32,
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

#[derive(Debug, Clone)]
pub struct Bond {
    pub atom1: AtomID,
    pub atom2: AtomID,
    pub order: i32,
}

pub struct Molecule {
    atoms: Vec<Atom>,
    bonds: Vec<Bond>,
    adjacency: HashMap<AtomID, Vec<AtomID>>,
    num_atoms: AtomID,
}

impl Molecule {
    pub fn new() -> Self {
        Self {
            atoms: Vec::new(),
            bonds: Vec::new(),
            adjacency: HashMap::new(),
            num_atoms: 0,
        }
    }

    pub fn add_atom(&mut self, element: &str, x: f64, y: f64, z: f64) -> AtomID {
        let atomic_number = get_atomic_number(element);
        let id = self.num_atoms;
        self.atoms.push(Atom {
            id,
            element: element.to_string(),
            atomic_number,
            x,
            y,
            z,
        });
        self.adjacency.insert(id, Vec::new());
        self.num_atoms += 1;
        id
    }

    pub fn add_bond(&mut self, a1: AtomID, a2: AtomID, order: i32) {
        self.bonds.push(Bond { atom1: a1, atom2: a2, order });
        self.adjacency.entry(a1).or_default().push(a2);
        self.adjacency.entry(a2).or_default().push(a1);
    }

    pub fn get_atoms(&self) -> &Vec<Atom> {
        &self.atoms
    }

    pub fn get_bonds(&self) -> &Vec<Bond> {
        &self.bonds
    }

    pub fn neighbors(&self, id: AtomID) -> Vec<AtomID> {
        self.adjacency.get(&id).cloned().unwrap_or_default()
    }

    pub fn empty(&self) -> bool {
        self.atoms.is_empty()
    }

    pub fn count_hbond_acceptors(&self) -> i32 {
        let mut count = 0;

        for atom in &self.atoms {
            let neighbor_ids = self.neighbors(atom.id);
            let total_bond_order: i32 = neighbor_ids
                .iter()
                .map(|&nid| get_bond_order(atom.id, nid, &self.bonds))
                .sum();

            if atom.element == "N" && total_bond_order == 3 {
                count += 1;
            }
            if atom.element == "O" && total_bond_order == 2 {
                count += 1;
            }
        }

        count
    }

    pub fn count_hbond_donors(&self) -> i32 {
        let mut count = 0;

        for atom in &self.atoms {
            let neighbor_ids = self.neighbors(atom.id);
            let total_bond_order: i32 = neighbor_ids
                .iter()
                .map(|&nid| get_bond_order(atom.id, nid, &self.bonds))
                .sum();

            if atom.element == "N" && total_bond_order == 3 {
                if neighbor_ids.iter().any(|&nid| self.atoms[nid].element == "H") {
                    count += 1;
                }
            }

            if atom.element == "O" && total_bond_order == 2 {
                if neighbor_ids.iter().any(|&nid| self.atoms[nid].element == "H") {
                    count += 1;
                }
            }
        }

        count
    }
}

fn get_atomic_number(element: &str) -> i32 {
    match element {
        "H" => 1,
        "C" => 6,
        "N" => 7,
        "O" => 8,
        _ => 0,
    }
}

/// Helper function to determine bond order between two atoms
pub fn get_bond_order(a1: AtomID, a2: AtomID, bonds: &[Bond]) -> i32 {
    for bond in bonds {
        if (bond.atom1 == a1 && bond.atom2 == a2) || (bond.atom1 == a2 && bond.atom2 == a1) {
            return bond.order;
        }
    }
    0
}
