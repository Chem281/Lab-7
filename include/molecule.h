#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

class Molecule {
    public:
        Molecule() {};

        using AtomID = int;
    
        struct Atom {
            AtomID id;
            std::string element;
            int atomic_number;
            double x, y, z;
        };
    
        struct Bond {
            AtomID atom1;
            AtomID atom2;
            int order;
        };
    
        AtomID add_atom(const std::string& element, double x, double y, double z);
        void add_bond(AtomID a1, AtomID a2, int order = 1);
        const std::vector<Atom>& get_atoms() const;
        const std::vector<Bond>& get_bonds() const;
        std::vector<AtomID> neighbors(AtomID id) const;
        int countHBondAcceptors() const;
        int countHBondDonors() const;
        bool empty() const;
    
    private:
        std::vector<Atom> atoms;
        std::vector<Bond> bonds;
        std::unordered_map<AtomID, std::vector<AtomID>> adjacency;
        AtomID num_atoms = 0;
};

std::vector<Molecule> load_from_mol2(const std::string& filename);

// Calculate geometric centroid of all molecules 
std::vector<std::vector<double>> geometric_centroid(const std::vector<Molecule>& mols);

// Generic filtering function, because it is templated it needs to be in the header!
template <typename InputIterator, typename Predicate>
std::vector<typename InputIterator::value_type>
filter(InputIterator begin, InputIterator end, Predicate pred)
{
    std::vector<typename InputIterator::value_type> result;
    std::copy_if(begin, end, std::back_inserter(result), pred);
    return result;
}

// Use the generic filtering function to create named lambdas to filter a set of molecules
std::vector<Molecule> filter_molecules(const std::vector<Molecule>& mols);
