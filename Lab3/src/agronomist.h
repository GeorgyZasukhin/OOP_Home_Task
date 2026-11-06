#pragma once

#include <string>

// Інваріант Agronomist:
// 1. Ім'я та спеціалізація містять непробільні символи.
// 2. Номер працівника невід'ємний і незмінний після створення.
// 3. Стаж належить [0, 80] рокам.
class Agronomist
{
public:
    Agronomist();
    explicit Agronomist(std::string name);
    Agronomist(std::string name, std::string specialization,
               int employeeId, int experienceYears);
    Agronomist(const Agronomist& other);
    ~Agronomist() noexcept;

    const std::string& name() const;
    const std::string& specialization() const;
    int employeeId() const;
    int experienceYears() const;
    bool isValid() const;

private:
    std::string name_;
    std::string specialization_;
    const int employeeId_;
    int experienceYears_ = 0;
};
