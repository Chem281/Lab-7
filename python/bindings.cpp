#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "molecule.h"  // your header file

namespace py = pybind11;

PYBIND11_MODULE(mol, m) {
    m.doc() = "Molecule bindings";

    py::class_<Molecule::Atom>(m, "Atom")
        .def_readonly("id", &Molecule::Atom::id)
        .def_readonly("element", &Molecule::Atom::element)
        .def_readonly("atomic_number", &Molecule::Atom::atomic_number)
        .def_readonly("x", &Molecule::Atom::x)
        .def_readonly("y", &Molecule::Atom::y)
        .def_readonly("z", &Molecule::Atom::z);

    py::class_<Molecule::Bond>(m, "Bond")
        .def_readonly("atom1", &Molecule::Bond::atom1)
        .def_readonly("atom2", &Molecule::Bond::atom2)
        .def_readonly("order", &Molecule::Bond::order);

    py::class_<Molecule>(m, "Molecule")
        .def(py::init<>())
        .def("add_atom", &Molecule::add_atom)
        .def("add_bond", &Molecule::add_bond)
        .def("get_atoms", &Molecule::get_atoms, py::return_value_policy::reference)
        .def("get_bonds", &Molecule::get_bonds, py::return_value_policy::reference)
        .def("neighbors", &Molecule::neighbors)
        .def("empty", &Molecule::empty);

    m.def("load_from_mol2", &load_from_mol2, "Load molecules from .mol2 file");
}