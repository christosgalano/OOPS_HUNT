#pragma once
#include "Attributes/Attribute.hpp"

/// The following classes represent the attributes of a hero ///

class Mana : public Attribute {
private:
    // At the end of each battle round a hero regenerates mana_factor % of their mana
    static constexpr double mana_factor {0.25};
public:
    // Constructor
    Mana(int in_mana) : Attribute(in_mana) {}

    // Methods
    void regenerateMana() {
        if (current_stat == base_stat)   return;

        int amount = static_cast<int>(base_stat * mana_factor);

        if (current_stat + amount > base_stat) {
            std::cout << " just regenarated " << base_stat - current_stat << " mana\n";       
            current_stat = base_stat;
        }
        else {
            std::cout << " just regenarated " << amount << " mana\n";
            current_stat += amount;
        }
    }

    void upgrade(int level) override {
        // Same logic used as in Health::upgrade(int)
        int diff = base_stat - current_stat;
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat - diff;
    }
};


class Strength : public Attribute {
public:
    // Constructor
    Strength(int in_strength) : Attribute(in_strength) {}

    // Method
    void upgrade(int level) override {
        // The hero's base_strength increases but we keep the current_strength equal to the sum new_base_strength + diff,
        // where diff is the difference between current_strength and base_strength that existed before we upgraded the last one.
        // We do this so that we don't lose the effect of a potion that is possibly in use.
        // The process is similar for Dexterity and Agility ...
        int diff = current_stat - base_stat;
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat + diff;
    }
};


class Dexterity : public Attribute {
public:
    // Constructor
    Dexterity(int in_dexterity) : Attribute(in_dexterity) {}

    // Method
    void upgrade(int level) override {
        int diff = current_stat - base_stat;
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat + diff;
    }
};


class Agility : public Attribute { 
private:
    // A hero's agility cannot exceed the limit of max_agility and that's because
    // otherwise the majority of a monster's attacks would never land.
    static constexpr int max_agility {60};
public:
    // Example: Agility = 10 means that the hero has a 10 / 100 chance to dodge an incoming attack.
    
    // Constructor
    Agility(int in_agility) : Attribute(in_agility) {}

    // Accessor
    int getMaxAgility() const { return max_agility; }

    // Method
    void upgrade(int level) override {
        int diff = current_stat - base_stat;
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat + diff;
    }
};