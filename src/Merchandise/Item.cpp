#include "Merchandise/Item.hpp"
#include <iostream>

Item::Item(const std::string& in_name, int in_price, int in_minimum_level)
    : Merchandise(in_name, in_price, in_minimum_level) {}

void Item::printPlain() const {
    std::cout << "Item: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level << '\n'; 
}


void Weapon::printDetailed() const {
    std::cout << "Weapon: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level;
    std::cout << ", Damage: " << damage << ", Hands required: " << hands_required << '\n';
}

void Weapon::printStatistics() const {
    std::cout << "Weapon: " << name << ", Damage: " << damage << ", Hands required: " << hands_required << '\n';    
}


void Armor::printDetailed() const {
    std::cout << "Armor: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level;
    std::cout << ", Damage reduction: " << reduced_damage << '\n';
}

void Armor::printStatistics() const {
    std::cout << "Armor: " << name << ", Damage reduction: " << reduced_damage << '\n';    
}


void Potion::printDetailed() const {
    std::cout << "Potion: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level;
    std::cout << ", Statistic increment: " << statistic_increment << '\n';
}

void Potion::printStatistics() const {
    std::cout << "Potion: " << name << ", Statistic increment: " << statistic_increment << '\n';   
}