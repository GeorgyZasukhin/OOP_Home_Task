#pragma once

#include <string>

// Навчальний журнал; кожен успішно створений об'єкт має свій dtor.
namespace lifetime
{
    int liveCount() noexcept;
    void created(const char* type, const std::string& name) noexcept;
    void destroyed(const char* type, const std::string& name) noexcept;
}
