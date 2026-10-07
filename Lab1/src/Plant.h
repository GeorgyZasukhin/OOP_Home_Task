#pragma once

#include <string>

class Plant {
public:
    Plant(std::string name, std::string family, int plantingYear, int heightCm);

    const std::string& name() const;
    const std::string& family() const;
    int plantingYear() const;
    int heightCm() const;

    bool isOlderThan(int year) const;

private:
    std::string name_;
    std::string family_;
    int plantingYear_;
    int heightCm_;
};
