#include "agronomist.h"
#include "seed_variety.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace
{
    SeedVariety globalVariety{"Global"};

    void touchStatic()
    {
        static SeedVariety localStatic{"LocalStatic"};
        (void)localStatic;
    }

    void createLeak()
    {
        // Навмисний витік лише в режимі --leak, для порівняння журналів.
        SeedVariety* forgotten = new SeedVariety{"Forgotten"};
        (void)forgotten;
    }

    void observe(const SeedVariety& variety)
    {
        std::clog << "observe " << variety.name() << '\n';
    }
}

int main(int argc, char* argv[])
{
    const bool leak = argc == 2 && std::string{argv[1]} == "--leak";
    if (argc > 2 || (argc == 2 && !leak))
    {
        std::cerr << "Usage: lifetime_demo [--leak]\n";
        return 1;
    }
    std::clog << "--- begin main ---\n";
    SeedVariety onStack{"Stack"};
    Agronomist observer{"Agronomist"};
    {
        SeedVariety inner{"Inner"};
    }
    touchStatic();
    touchStatic();

    std::unique_ptr<SeedVariety> repaired;
    if (leak)
    {
        createLeak();
    }
    else
    {
        repaired = std::make_unique<SeedVariety>("Repaired");
    }
    auto owned = std::make_unique<SeedVariety>("Owned");
    std::vector<SeedVariety> stock;
    stock.reserve(2);
    stock.emplace_back("Vector");
    observe(SeedVariety{"Temporary"});
    std::clog << "--- end main ---\n";
    return 0;
}
