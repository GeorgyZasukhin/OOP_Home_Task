#pragma once

#include "ingredient.h"

#include <utility>
#include <vector>

class IngredientListV2
{
public:
    void add(Ingredient ingredient)
    {
        items_.push_back(std::move(ingredient));
    }

    Ingredient& at(std::size_t index)
    {
        return items_.at(index);
    }

    const Ingredient& at(std::size_t index) const
    {
        return items_.at(index);
    }

    std::size_t size() const noexcept
    {
        return items_.size();
    }

private:
    std::vector<Ingredient> items_;
};
