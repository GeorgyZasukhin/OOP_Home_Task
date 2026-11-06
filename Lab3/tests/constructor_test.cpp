#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "agronomist.h"
#include "seed_variety.h"
#include "lifetime_log.h"

#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

static_assert(!std::is_convertible_v<std::string, SeedVariety>);
static_assert(!std::is_convertible_v<std::string, Agronomist>);
static_assert(std::is_nothrow_destructible_v<SeedVariety>);
static_assert(std::is_nothrow_destructible_v<Agronomist>);

TEST_CASE("case_1")
{
    SeedVariety v{};
    CHECK(v.isValid());
    CHECK(v.name() == "Unnamed");
    CHECK(v.yieldTonPerHa() == 0.0);
    CHECK(v.registrationYear() == 1900);
}
TEST_CASE("case_2")
{
    SeedVariety v{"Podolianka", "Wheat", 6.5, 2003};
    CHECK(v.isValid());
    CHECK(v.name() == "Podolianka");
    CHECK(v.crop() == "Wheat");
    CHECK(v.yieldTonPerHa() == 6.5);
    CHECK(v.registrationYear() == 2003);
}
TEST_CASE("case_3")
{
    SeedVariety v{"Short"};
    CHECK(v.isValid());
    CHECK(v.name() == "Short");
    CHECK(v.registrationYear() == 1900);
    CHECK(v.crop() == "Unknown");
}
TEST_CASE("case_4")
{
    CHECK_THROWS_AS((SeedVariety{""}), std::invalid_argument);
    CHECK_THROWS_AS((SeedVariety{" \t"}), std::invalid_argument);
    CHECK_THROWS_AS((SeedVariety{"X", "", 1, 2000}),
                    std::invalid_argument);
}
TEST_CASE("case_5")
{
    CHECK(SeedVariety{"A", "B", 0, 1900}.isValid());
    CHECK(SeedVariety{"A", "B", 100, 2100}.isValid());
    CHECK_THROWS_AS((SeedVariety{"A", "B", 1, 1899}),
                    std::out_of_range);
    CHECK_THROWS_AS((SeedVariety{"A", "B", 1, 2101}),
                    std::out_of_range);
}
TEST_CASE("case_6")
{
    for (double value : {-1.0, 100.1,
         std::numeric_limits<double>::infinity(),
         std::numeric_limits<double>::quiet_NaN()})
    {
        CHECK_THROWS_AS((SeedVariety{"A", "B", value, 2000}),
                        std::out_of_range);
    }
}
TEST_CASE("case_7")
{
    Agronomist a{};
    CHECK(a.isValid());
    CHECK(a.employeeId() == 0);
    CHECK(a.experienceYears() == 0);
}
TEST_CASE("case_8")
{
    Agronomist a{"Olena", "Cereals", 9, 8};
    CHECK(a.isValid());
    CHECK(a.name() == "Olena");
    CHECK(a.specialization() == "Cereals");
    CHECK(a.employeeId() == 9);
    CHECK(a.experienceYears() == 8);
}
TEST_CASE("case_9")
{
    Agronomist a{"Short"};
    CHECK(a.isValid());
    CHECK(a.specialization() == "General");
}
TEST_CASE("case_10")
{
    CHECK_THROWS_AS((Agronomist{""}), std::invalid_argument);
    CHECK_THROWS_AS((Agronomist{" \n"}), std::invalid_argument);
    CHECK_THROWS_AS((Agronomist{"A", "", 1, 0}),
                    std::invalid_argument);
}
TEST_CASE("case_11")
{
    CHECK_THROWS_AS((Agronomist{"A", "B", -1, 0}),
                    std::out_of_range);
}
TEST_CASE("case_12")
{
    CHECK(Agronomist{"A", "B", 0, 0}.isValid());
    CHECK(Agronomist{"A", "B", 1, 80}.isValid());
    CHECK_THROWS_AS((Agronomist{"A", "B", 1, -1}),
                    std::out_of_range);
    CHECK_THROWS_AS((Agronomist{"A", "B", 1, 81}),
                    std::out_of_range);
}
TEST_CASE("case_13")
{
    const int before = lifetime::liveCount();
    {
        SeedVariety v{};
        CHECK(lifetime::liveCount() == before + 1);
        {
            Agronomist a{};
            CHECK(a.isValid());
            CHECK(lifetime::liveCount() == before + 2);
        }
        CHECK(v.isValid());
        CHECK(lifetime::liveCount() == before + 1);
    }
    CHECK(lifetime::liveCount() == before);
}
TEST_CASE("case_14")
{
    const int before = lifetime::liveCount();
    try
    {
        SeedVariety valid{};
        Agronomist invalid{"A", "B", -1, 0};
        FAIL("Constructor must throw");
    }
    catch (const std::out_of_range&)
    {
        CHECK(lifetime::liveCount() == before);
    }
}
TEST_CASE("case_15")
{
    const int before = lifetime::liveCount();
    {
        SeedVariety original{};
        SeedVariety copy{original};
        Agronomist first{};
        Agronomist second{first};
        CHECK(copy.isValid());
        CHECK(second.isValid());
        CHECK(copy.name() == original.name());
        std::vector<SeedVariety> items;
        items.reserve(1);
        items.emplace_back("First");
        items.emplace_back("Second");
        CHECK(items[0].isValid());
        CHECK(items[1].isValid());
        CHECK(lifetime::liveCount() == before + 6);
    }
    CHECK(lifetime::liveCount() == before);
}
TEST_CASE("case_16")
{
    const int before = lifetime::liveCount();
    {
        auto item = std::make_unique<SeedVariety>("Owned");
        CHECK(item->isValid());
        CHECK(lifetime::liveCount() == before + 1);
        CHECK(SeedVariety{"Temporary"}.isValid());
        CHECK(lifetime::liveCount() == before + 1);
    }
    CHECK(lifetime::liveCount() == before);
}
