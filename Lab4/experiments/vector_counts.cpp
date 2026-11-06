#include "ingredient_list.h"

#include <iostream>
#include <type_traits>
#include <vector>

int main()
{
    IngredientList::resetCounts();
    std::vector<IngredientList> lists;
    for (int i = 0; i < 8; ++i)
    {
        lists.emplace_back().add({"Tomato", 150});
    }
    std::cout << std::boolalpha << "nothrow move: "
              << std::is_nothrow_move_constructible_v<IngredientList>
              << "\ncopies: " << IngredientList::copies()
              << "\nmoves: " << IngredientList::moves() << '\n';
}
