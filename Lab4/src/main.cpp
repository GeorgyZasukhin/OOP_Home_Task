#include "dish.h"

#include <iostream>

void printDish(Dish copy)
{
    std::cout << copy.name() << ":\n";
    for (std::size_t i = 0; i < copy.ingredientCount(); ++i)
    {
        const Ingredient& item = copy.ingredientAt(i);
        std::cout << "  " << item.name << ": " << item.grams << " g\n";
    }
}

int main()
{
    Menu menu;
    menu.emplace_back("Tomato salad");
    menu.at(0).addIngredient({"Tomato", 150});
    menu.at(0).addIngredient({"Olive oil", 15});
    printDish(menu.at(0));

    const Menu saved = menu;
    menu.at(0).ingredientAt(0).grams = 200;
    std::cout << "Original: " << menu.at(0).ingredientAt(0).grams << " g\n";
    std::cout << "Menu copy: " << saved.at(0).ingredientAt(0).grams << " g\n";

    Dish& dish = menu.at(0);
    const Dish& sameDish = dish;
    const auto before = dish.ingredientCount();
    dish = sameDish;
    std::cout << "Self-assignment: " << before << " -> "
              << dish.ingredientCount() << '\n';
}
