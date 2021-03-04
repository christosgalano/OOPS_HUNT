#pragma once
#include "Entities/Hero.hpp"

/// Types of Hero ///

class Warrior : public Hero {   
public:
    // Constructor
    Warrior(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility);

    // Method
    void printDetailed() const override;
};


class Sorcerer : public Hero {
public:
    // Constructor
    Sorcerer(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility);

    // Method
    void printDetailed() const override;
};


class Paladin : public Hero {   
public:
    // Constructor
    Paladin(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility);

    // Method
    void printDetailed() const override;
};