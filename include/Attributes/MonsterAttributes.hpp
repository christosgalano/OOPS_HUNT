#pragma once
#include "Attributes/Attribute.hpp"

/// The following classes represent the attributes of a monster ///

class DamageRange : public Attribute {
public:
    // Constructor
    DamageRange(int in_damage_range) : Attribute(in_damage_range) {}
    
    // Method
    void upgrade(int level) override {
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat;
    }
};


class Defense : public Attribute {
public:
    // Constructor
    Defense(int in_defense) : Attribute(in_defense) {}

    // Method
    void upgrade(int level) override {
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat;
    }
};


class Dodge : public Attribute { 
private:
    // A monster's chance to dodge can't exceed the limit of max_dodge and that's because
    // otherwise the majority of a hero's attacks would never land.
    static constexpr int max_dodge {60};
public:
    // Example: Dodge = 10 means that the monster has a 10 / 100 chance to dodge an incoming attack.
    
    // Constructor
    Dodge(int in_dodge) : Attribute(in_dodge) {}

    // Accessor
    int getMaxDodge() const { return max_dodge; }

    // Method
    void upgrade(int level) override {
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat;
    }
};