import matplotlib.pyplot as plt

import os
import sys

project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# Append 'build' folder from project root
sys.path.append(os.path.join(project_root, 'build'))
import mol

# Sample data
mols = mol.load_from_mol2("../files/mols.mol2")

# Get the coordinates for the first molecule and its geometric center
mol_coordinates = [[atom.x, atom.y, atom.z] for atom in mols[0].get_atoms()]
x, y, z = zip(*mol_coordinates)
geometric_center = mol.geometric_centroid(mols)[0]

# Create 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z, c='blue', s=50)
ax.scatter(geometric_center[0], geometric_center[1], geometric_center[2], c='red', s=70)

# Optional: labels
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')
plt.title('Geometric Center of Molecule')

# Save the figure
plt.savefig('mol_geo_center.png', dpi=300, bbox_inches='tight')