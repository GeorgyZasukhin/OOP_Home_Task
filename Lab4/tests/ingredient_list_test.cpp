#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dish.h"
#include "ingredient_list_v2.h"

#include <stdexcept>
#include <type_traits>
#include <utility>

static_assert(std::is_nothrow_move_constructible_v<IngredientList>);
static_assert(std::is_nothrow_move_assignable_v<IngredientList>);

TEST_CASE_TEMPLATE("Copy creates a separate array", List,
                   IngredientList, IngredientListV2)
{
    List source;
    source.add({"Tomato", 150});
    List copy{source};
    REQUIRE(copy.getSize() == 1);
    CHECK(copy.getAt(0).name == "Tomato");
    CHECK(&copy.getAt(0) != &source.getAt(0));
}

TEST_CASE_TEMPLATE("Changes do not affect a copy", List,
                   IngredientList, IngredientListV2)
{
    List source;
    source.add({"Tomato", 150});
    List copy{source};
    source.getAt(0) = {"Cucumber", 80};
    CHECK(copy.getAt(0).name == "Tomato");
    CHECK(copy.getAt(0).grams == 150);
}

TEST_CASE_TEMPLATE("Copy assignment replaces existing and empty lists", List,
                   IngredientList, IngredientListV2)
{
    List source;
    source.add({"Tomato", 150});
    List full;
    full.add({"Onion", 25});
    List empty;
    full = source;
    empty = source;
    REQUIRE(full.getSize() == 1);
    REQUIRE(empty.getSize() == 1);
    CHECK(full.getAt(0).name == "Tomato");
    CHECK(empty.getAt(0).grams == 150);
    source.getAt(0).grams = 200;
    CHECK(full.getAt(0).grams == 150);
    CHECK(empty.getAt(0).grams == 150);
    const List blank;
    full = blank;
    CHECK(full.getSize() == 0);
}

TEST_CASE_TEMPLATE("Copy self-assignment preserves contents", List,
                   IngredientList, IngredientListV2)
{
    List list;
    list.add({"Tomato", 150});
    const List& same = list;
    list = same;
    REQUIRE(list.getSize() == 1);
    CHECK(list.getAt(0).grams == 150);
}

TEST_CASE_TEMPLATE("Move construction transfers contents", List,
                   IngredientList, IngredientListV2)
{
    List source;
    source.add({"Tomato", 150});
    List target{std::move(source)};
    REQUIRE(target.getSize() == 1);
    CHECK(target.getAt(0).name == "Tomato");
    if constexpr (std::is_same_v<List, IngredientList>)
    {
        CHECK(source.getSize() == 0);
        CHECK_THROWS_AS(source.getAt(0), std::out_of_range);
    }
    source.add({"New", 1});
    CHECK(source.getAt(source.getSize() - 1).name == "New");
}

TEST_CASE_TEMPLATE("Move assignment replaces the old resource", List,
                   IngredientList, IngredientListV2)
{
    List source;
    source.add({"Tomato", 150});
    List target;
    target.add({"Onion", 25});
    target = std::move(source);
    REQUIRE(target.getSize() == 1);
    CHECK(target.getAt(0).name == "Tomato");
    if constexpr (std::is_same_v<List, IngredientList>)
    {
        CHECK(source.getSize() == 0);
    }
    source.add({"New", 1});
    CHECK(source.getAt(source.getSize() - 1).name == "New");
}

TEST_CASE_TEMPLATE("Growth, bounds and destruction after scope", List,
                   IngredientList, IngredientListV2)
{
    {
        List list;
        CHECK_THROWS_AS(list.getAt(0), std::out_of_range);
        list.add({"Tomato", 150});
        list.add(list.getAt(0));
        list.add({"Oil", 15});
        const List& readOnly = list;
        REQUIRE(readOnly.getSize() == 3);
        CHECK(readOnly.getAt(1).name == "Tomato");
        CHECK(readOnly.getAt(2).grams == 15);
        CHECK_THROWS_AS(readOnly.getAt(3), std::out_of_range);
    } // ASan verifies that destruction leaves no invalid access.
}

TEST_CASE("Manual move self-assignment preserves the resource")
{
    IngredientList list;
    list.add({"Oil", 15});
    IngredientList& same = list;
    list = std::move(same);
    REQUIRE(list.getSize() == 1);
    CHECK(list.getAt(0).grams == 15);
}

TEST_CASE("Copying a menu preserves the original recipe")
{
    Menu menu;
    menu.emplace_back("Salad");
    menu.at(0).addIngredient({"Tomato", 150});
    const Menu copy = menu;
    menu.at(0).getIngredientAt(0).grams = 200;
    CHECK(copy.at(0).getIngredientAt(0).grams == 150);
}
