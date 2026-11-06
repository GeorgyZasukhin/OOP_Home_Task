#pragma once

#include "ingredient_list.h"

#include <string>
#include <vector>

class Dish
{
public:
    explicit Dish(std::string name);
    void addIngredient(Ingredient ingredient);
    Ingredient& ingredientAt(std::size_t index);
    const Ingredient& ingredientAt(std::size_t index) const;
    std::size_t ingredientCount() const noexcept;
    const std::string& name() const noexcept;

private:
    std::string name_;
    IngredientList ingredients_;
};

using Menu = std::vector<Dish>;
