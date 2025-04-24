from rdkit import Chem
from rdkit.Chem import AllChem
import os

def smiles_to_mol_batch(input_smi, output_dir):
    os.makedirs(output_dir, exist_ok=True)

    with open(input_smi, 'r') as f:
        for i, line in enumerate(f):
            parts = line.strip().split()
            if not parts:
                continue
            smi = parts[0]
            name = parts[1] if len(parts) > 1 else f"mol_{i}"

            mol = Chem.MolFromSmiles(smi)
            if mol is None:
                print(f"[{i}] Failed to parse SMILES: {smi}")
                continue

            mol = Chem.AddHs(mol)
            try:
                success = AllChem.EmbedMolecule(mol, maxAttempts=10)
                if success != 0:
                    raise ValueError("Embedding failed")
                AllChem.UFFOptimizeMolecule(mol)
            except Exception as e:
                print(f"[{i}] 3D generation failed for {name}: {e}")
                continue

            output_path = os.path.join(output_dir, f"{name}.mol")
            try:
                Chem.MolToMolFile(mol, output_path)
            except Exception as e:
                print(f"[{i}] Failed to write MOL2 for {name}: {e}")
                continue

            print(f"[{i}] Wrote {output_path}")

# Example usage:
smiles_to_mol_batch("../files/mols.smi", "../files/mols")