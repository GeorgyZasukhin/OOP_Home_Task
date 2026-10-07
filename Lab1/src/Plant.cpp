#include "Plant.h"

#include <utility>

Plant::Plant(std::string name, std::string family, int plantingYear, int heightCm)
    : name_(std::move(name)),
      family_(std::move(family)),
      plantingYear_(plantingYear),
      heightCm_(heightCm) {}

const std::string& Plant::name() const {
    return name_;
}

const std::string& Plant::family() const {
    return family_;
}

int Plant::plantingYear() const {
    return plantingYear_;
}

int Plant::heightCm() const {
    return heightCm_;
}

bool Plant::isOlderThan(int year) const {
    return plantingYear_ < year;
}
