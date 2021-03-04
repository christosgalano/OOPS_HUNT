#pragma once
#include "Entities/Monster.hpp"

/// Types of Monster ///

class Dragon : public Monster {
public:
    // Constructor
    Dragon(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge);

    // Method
    void printDetailed() const override;
};


class Exoskeleton : public Monster {
public:
    // Constructor
    Exoskeleton(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge);

    // Method
    void printDetailed() const override;
};


class Spirit : public Monster {
public:
    // Constructor
    Spirit(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge);

    // Method
    void printDetailed() const override;
};