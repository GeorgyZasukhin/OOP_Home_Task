#include "dish.h"

#include <utility>

Dish::Dish(std::string name)
    : name_(std::move(name))
{
}

void Dish::addIngredient(Ingredient ingredient)
{
    ingredients_.add(std::move(ingredient));
}

Ingredient& Dish::getIngredientAt(std::size_t index)
{
    return ingredients_.getAt(index);
}

const Ingredient& Dish::getIngredientAt(std::size_t index) const
{
    return ingredients_.getAt(index);
}

std::size_t Dish::getIngredientCount() const noexcept
{
    return ingredients_.getSize();
}

const std::string& Dish::getName() const noexcept
{
    return name_;
}
