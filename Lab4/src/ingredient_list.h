#pragma once

#include "ingredient.h"

#include <cstddef>

class IngredientList
{
public:
    IngredientList() = default;

    // Звільняє власний масив через delete[].
    ~IngredientList();

    // Виділяє окремий масив і копіює інгредієнти.
    IngredientList(const IngredientList& other);

    // Готує глибоку копію перед обміном ресурсами.
    IngredientList& operator=(const IngredientList& other);

    // Забирає масив і залишає джерело порожнім.
#ifdef LAB4_MOVE_MAY_THROW
    IngredientList(IngredientList&& other);
#else
    IngredientList(IngredientList&& other) noexcept;
#endif

    // Звільняє старий масив і забирає ресурс джерела.
    IngredientList& operator=(IngredientList&& other) noexcept;

    void add(Ingredient ingredient);
    Ingredient& at(std::size_t index);
    const Ingredient& at(std::size_t index) const;
    std::size_t size() const noexcept;

    static void resetCounts() noexcept;
    static std::size_t copies() noexcept;
    static std::size_t moves() noexcept;

    friend void swap(IngredientList& first, IngredientList& second) noexcept;

private:
    // Інваріант: size_ <= capacity_; items_ належить тільки цьому списку.
    // items_ == nullptr тоді й лише тоді, коли capacity_ == 0.
    Ingredient* items_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
    static std::size_t copies_;
    static std::size_t moves_;
};
