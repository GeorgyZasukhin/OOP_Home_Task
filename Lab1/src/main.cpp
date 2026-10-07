#include "Plant.h"

#include <iostream>
#include <vector>

int main() {
    const std::vector<Plant> plants{
        {"European beech", "Fagaceae", 2010, 350},
        {"Common lilac", "Oleaceae", 2018, 180},
        {"Norway maple", "Sapindaceae", 2005, 620},
        {"Garden rose", "Rosaceae", 2022, 95},
    };

    constexpr int referenceYear = 2000;

    for (const auto& plant : plants) {
        std::cout << "Name: " << plant.name()
                  << "; family: " << plant.family()
                  << "; planting year: " << plant.plantingYear()
                  << "; height: " << plant.heightCm() << " cm"
                  << "; older than " << referenceYear << ": "
                  << (plant.isOlderThan(referenceYear) ? "yes" : "no")
                  << '\n';
    }

    return 0;
}
