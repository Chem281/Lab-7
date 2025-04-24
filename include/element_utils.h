#include <string>
#include <unordered_map>

inline int get_atomic_number(const std::string& element) {
    static const std::unordered_map<std::string, int> element_table = {
        {"H", 1}, {"He", 2}, {"Li", 3}, {"Be", 4}, {"B", 5}, {"C", 6}, {"N", 7}, {"O", 8},
        {"F", 9}, {"Ne", 10}, {"Na", 11}, {"Mg", 12}, {"Al", 13}, {"Si", 14}, {"P", 15},
        {"S", 16}, {"Cl", 17}, {"Ar", 18}, {"K", 19}, {"Ca", 20}, // extend as needed
    };

    auto it = element_table.find(element);
    if (it != element_table.end()) {
        return it->second;
    }
    return 0; // Unknown element
}