// Цей файл навмисно не повинен компілюватися через explicit.
#include "seed_variety.h"

#include <string>

int main()
{
    SeedVariety variety = std::string{"Implicit"};
    (void)variety;
}
