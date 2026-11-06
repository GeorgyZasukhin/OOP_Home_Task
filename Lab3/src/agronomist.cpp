#include "agronomist.h"
#include "lifetime_log.h"

#include <stdexcept>
#include <utility>

Agronomist::Agronomist()
    : Agronomist("Unnamed", "General", 0, 0)
{
}

Agronomist::Agronomist(std::string name)
    : Agronomist(std::move(name), "General", 0, 0)
{
}

Agronomist::Agronomist(std::string name, std::string specialization,
                       int employeeId, int experienceYears)
    : name_(std::move(name)),
      specialization_(std::move(specialization)),
      employeeId_(employeeId),
      experienceYears_(experienceYears)
{
    if (name_.find_first_not_of(" \t\n\r\f\v") == std::string::npos
        || specialization_.find_first_not_of(" \t\n\r\f\v")
            == std::string::npos)
    {
        throw std::invalid_argument("name and specialization need text");
    }
    if (employeeId_ < 0)
    {
        throw std::out_of_range("employee id must be nonnegative");
    }
    if (experienceYears_ < 0 || experienceYears_ > 80)
    {
        throw std::out_of_range("experience must be in [0, 80]");
    }
    lifetime::created("Agronomist", name_);
}

Agronomist::Agronomist(const Agronomist& other)
    : Agronomist(other.name_, other.specialization_, other.employeeId_,
                 other.experienceYears_)
{
}

Agronomist::~Agronomist() noexcept
{
    lifetime::destroyed("Agronomist", name_);
}

const std::string& Agronomist::name() const
{
    return name_;
}

const std::string& Agronomist::specialization() const
{
    return specialization_;
}

int Agronomist::employeeId() const
{
    return employeeId_;
}

int Agronomist::experienceYears() const
{
    return experienceYears_;
}

bool Agronomist::isValid() const
{
    return name_.find_first_not_of(" \t\n\r\f\v") != std::string::npos
        && specialization_.find_first_not_of(" \t\n\r\f\v")
            != std::string::npos
        && employeeId_ >= 0
        && experienceYears_ >= 0 && experienceYears_ <= 80;
}
