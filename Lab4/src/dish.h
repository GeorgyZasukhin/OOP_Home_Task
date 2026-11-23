#pragma once

#include "ingredient_list.h"

#include <string>
#include <vector>

class Dish
{
public:
    explicit Dish(std::string name);
    void addIngredient(Ingredient ingredient);
    Ingredient& getIngredientAt(std::size_t index);
    const Ingredient& getIngredientAt(std::size_t index) const;
    std::size_t getIngredientCount() const noexcept;
    const std::string& getName() const noexcept;

private:
    std::string name_;
    IngredientList ingredients_;
};

using Menu = std::vector<Dish>;
