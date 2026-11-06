// Навмисно хибна копія для окремого компіляторного досліду.
#include "seed_variety.h"
#include "lifetime_log.h"

#include <cmath>
#include <stdexcept>
#include <utility>

SeedVariety::SeedVariety()
    : SeedVariety("Unnamed", "Unknown", 0.0, 1900)
{
}

SeedVariety::SeedVariety(std::string name)
    : SeedVariety(std::move(name), "Unknown", 0.0, 1900)
{
}

SeedVariety::SeedVariety(std::string name, std::string crop,
                         double yieldTonPerHa, int registrationYear)
    : name_(std::move(name)),
      crop_(std::move(crop)),
      registrationYear_(registrationYear),
      yieldTonPerHa_(yieldTonPerHa)
{
    if (name_.find_first_not_of(" \t\n\r\f\v") == std::string::npos
        || crop_.find_first_not_of(" \t\n\r\f\v") == std::string::npos)
    {
        throw std::invalid_argument("name and crop must contain text");
    }
    if (!std::isfinite(yieldTonPerHa_) || yieldTonPerHa_ < 0.0
        || yieldTonPerHa_ > 100.0)
    {
        throw std::out_of_range("yield must be in [0, 100] t/ha");
    }
    if (registrationYear_ < 1900 || registrationYear_ > 2100)
    {
        throw std::out_of_range("registration year must be in [1900, 2100]");
    }
    // Рахуємо об'єкт лише після всіх перевірок.
    lifetime::created("SeedVariety", name_);
}

// Копія теж є окремим об'єктом і потребує власної пари ctor/dtor.
SeedVariety::SeedVariety(const SeedVariety& other)
    : SeedVariety(other.name_, other.crop_, other.yieldTonPerHa_,
                  other.registrationYear_)
{
}

SeedVariety::~SeedVariety() noexcept
{
    lifetime::destroyed("SeedVariety", name_);
}

const std::string& SeedVariety::name() const
{
    return name_;
}

const std::string& SeedVariety::crop() const
{
    return crop_;
}

double SeedVariety::yieldTonPerHa() const
{
    return yieldTonPerHa_;
}

int SeedVariety::registrationYear() const
{
    return registrationYear_;
}

bool SeedVariety::isValid() const
{
    return name_.find_first_not_of(" \t\n\r\f\v") != std::string::npos
        && crop_.find_first_not_of(" \t\n\r\f\v") != std::string::npos
        && std::isfinite(yieldTonPerHa_)
        && yieldTonPerHa_ >= 0.0 && yieldTonPerHa_ <= 100.0
        && registrationYear_ >= 1900 && registrationYear_ <= 2100;
}
