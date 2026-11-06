#include "agronomist.h"
#include "seed_variety.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        const SeedVariety variety{"Podolianka", "Wheat", 6.5, 2003};
        const Agronomist agronomist{"Olena Kovalenko", "Cereals", 9, 8};

        std::cout << "Variety: " << variety.name()
                  << "; crop: " << variety.crop()
                  << "; yield: " << variety.yieldTonPerHa() << " t/ha"
                  << "; registration year: "
                  << variety.registrationYear() << '\n'
                  << "Agronomist: " << agronomist.name()
                  << "; specialization: " << agronomist.specialization()
                  << "; employee id: " << agronomist.employeeId()
                  << "; experience: " << agronomist.experienceYears()
                  << " years\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
