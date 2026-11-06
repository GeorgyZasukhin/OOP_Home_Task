#include "ingredient.h"

#include <iostream>

class BrokenIngredientList
{
public:
    BrokenIngredientList()
        : items_(new Ingredient[2]{{"Tomato", 150}, {"Olive oil", 15}})
    {
    }

#ifndef LAB4_NO_DESTRUCTOR
    ~BrokenIngredientList()
    {
        delete[] items_;
    }
#endif

    const Ingredient& at(std::size_t index) const
    {
        return items_[index];
    }

private:
    Ingredient* items_;
};

void printIngredients(BrokenIngredientList copy)
{
    std::cout << copy.at(0).name << '\n' << copy.at(1).name << std::endl;
}

int main()
{
    BrokenIngredientList list;
    printIngredients(list);
}
