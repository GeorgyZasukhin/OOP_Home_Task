#include "ingredient_list.h"

#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

std::size_t IngredientList::copies_ = 0;
std::size_t IngredientList::moves_ = 0;

IngredientList::~IngredientList()
{
    delete[] items_;
}

IngredientList::IngredientList(const IngredientList& other)
    : size_(other.size_), capacity_(other.capacity_)
{
    if (capacity_ != 0)
    {
        std::unique_ptr<Ingredient[]> copy{new Ingredient[capacity_]};
        for (std::size_t i = 0; i < size_; ++i)
        {
            copy[i] = other.items_[i];
        }
        items_ = copy.release();
    }
    ++copies_;
}

IngredientList& IngredientList::operator=(const IngredientList& other)
{
    IngredientList copy{other};
    swap(*this, copy);
    return *this;
}

IngredientList::IngredientList(IngredientList&& other)
#ifndef LAB4_MOVE_MAY_THROW
    noexcept
#endif
    : items_(std::exchange(other.items_, nullptr)),
      size_(std::exchange(other.size_, 0)),
      capacity_(std::exchange(other.capacity_, 0))
{
    ++moves_;
}

IngredientList& IngredientList::operator=(IngredientList&& other) noexcept
{
    if (this != &other)
    {
        delete[] items_;
        items_ = std::exchange(other.items_, nullptr);
        size_ = std::exchange(other.size_, 0);
        capacity_ = std::exchange(other.capacity_, 0);
    }
    return *this;
}

void swap(IngredientList& first, IngredientList& second) noexcept
{
    using std::swap;
    swap(first.items_, second.items_);
    swap(first.size_, second.size_);
    swap(first.capacity_, second.capacity_);
}

void IngredientList::add(Ingredient ingredient)
{
    if (size_ == capacity_)
    {
        if (capacity_ > std::numeric_limits<std::size_t>::max() / 2)
        {
            throw std::length_error("Ingredient list is too large");
        }
        const std::size_t capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        std::unique_ptr<Ingredient[]> expanded{new Ingredient[capacity]};
        for (std::size_t i = 0; i < size_; ++i)
        {
            expanded[i] = std::move(items_[i]);
        }
        delete[] items_;
        items_ = expanded.release();
        capacity_ = capacity;
    }
    items_[size_] = std::move(ingredient);
    ++size_;
}

Ingredient& IngredientList::at(std::size_t index)
{
    return const_cast<Ingredient&>(std::as_const(*this).at(index));
}

const Ingredient& IngredientList::at(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Ingredient index is out of range");
    }
    return items_[index];
}

std::size_t IngredientList::size() const noexcept
{
    return size_;
}

void IngredientList::resetCounts() noexcept
{
    copies_ = 0;
    moves_ = 0;
}

std::size_t IngredientList::copies() noexcept
{
    return copies_;
}

std::size_t IngredientList::moves() noexcept
{
    return moves_;
}
