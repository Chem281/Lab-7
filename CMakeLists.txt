cmake_minimum_required(VERSION 3.14)
project(Molecule VERSION 1.0
	             DESCRIPTION "A class to represent molecules"
		         LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Find pybind11
find_package(pybind11 REQUIRED)
# find_package(OpenMP REQUIRED)
find_package(OpenMP REQUIRED)

# Include directories
include_directories(mol_exe include)

# Add executable
add_executable(mol_exe src/main.cpp src/molecule.cpp)
target_link_libraries(mol_exe PUBLIC OpenMP::OpenMP_CXX)

# Add the Python bindings via library
add_library(mol_lib SHARED src/molecule.cpp)
target_link_libraries(mol_lib PUBLIC OpenMP::OpenMP_CXX)
pybind11_add_module(mol python/bindings.cpp)
target_link_libraries(mol PRIVATE mol_lib)