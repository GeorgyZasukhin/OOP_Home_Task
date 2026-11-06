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

Ingredient& Dish::ingredientAt(std::size_t index)
{
    return ingredients_.at(index);
}

const Ingredient& Dish::ingredientAt(std::size_t index) const
{
    return ingredients_.at(index);
}

std::size_t Dish::ingredientCount() const noexcept
{
    return ingredients_.size();
}

const std::string& Dish::name() const noexcept
{
    return name_;
}
