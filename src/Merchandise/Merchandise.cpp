#include "Merchandise/Merchandise.hpp"
#include "Entities/Living.hpp"
#include "Utilities/Random.hpp"

Merchandise::Merchandise(const std::string& in_name, int in_price, int in_minimum_level)
    : name(in_name), price(in_price), minimum_level(in_minimum_level), initial_price(in_price) {}

void Merchandise::adjust(int level) {
    adjustPrice(level);
    adjustMinimumLevel(level);
}

void Merchandise::adjustPrice(int level) {
    // New price will be the product of initial_price * level
    price = initial_price * level;
}

void Merchandise::adjustMinimumLevel(int level) {
    // New level will belong in [level - 2, level + 1] where level = max_hero_level,
    // provided that new_level >= Living::base_level && new_level <= Living::max_level.
    RandomInt rnd {-2, 1};
    minimum_level = level + rnd(); 
    if (minimum_level > Living::getMaxLevel())
        minimum_level = Living::getMaxLevel();
    else if (minimum_level < Living::getBaseLevel())
        minimum_level = Living::getBaseLevel();
}