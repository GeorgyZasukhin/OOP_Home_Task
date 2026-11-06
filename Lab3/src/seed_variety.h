#pragma once

#include <string>

// Інваріант SeedVariety:
// 1. Назва сорту та культура містять непробільні символи.
// 2. Урожайність — скінченне число у межах [0, 100] т/га.
// 3. Рік районування належить [1900, 2100] і незмінний після створення.
// 4. Кожен успішний конструктор додає об'єкт до журналу один раз.
class SeedVariety
{
public:
    SeedVariety();
    explicit SeedVariety(std::string name);
    SeedVariety(std::string name, std::string crop,
                double yieldTonPerHa, int registrationYear);
    SeedVariety(const SeedVariety& other);
    ~SeedVariety() noexcept;

    const std::string& name() const;
    const std::string& crop() const;
    double yieldTonPerHa() const;
    int registrationYear() const;
    bool isValid() const;

private:
    std::string name_;
    std::string crop_;
    double yieldTonPerHa_ = 0.0;
    const int registrationYear_;
};
