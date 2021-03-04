#pragma once
#include "Attributes/Health.hpp"

/// Abstract class that represents a living being ///

class Living {
protected:
    std::string name;
    Health hp;
    int level;                          
    static constexpr int base_level {1};    // A being begins at level 1
    static constexpr int max_level {60};    // A being's level cannot exceed max_level
    
    // The amount of damage a being will deal in case its attack_damage - hero's armor/monster's defense  < minimum_damage.
    // Since at the end of each round each living being regenerates 10% of its base_hp minimum_damage will be 
    // minimum_damage_factor% of the being's that is under attack base_hp, reagardless of the being's armor/defense.
    // Although when the round ends it will generate 10% of its hp back, so the total damage will be
    // minimum_damage_factor% - 10% of its hp which is a very small amount.
    static constexpr double minimum_damage_factor {0.15};

public:
    // Constructor - Destructor
    Living(const std::string& in_name, int in_health)
        : name(in_name), hp(in_health), level(base_level) {}
    virtual ~Living() {}

    // Accessors
    std::string getName()   const { return name;               }
    int getLevel()          const { return level;              }
    int getHealth()         const { return hp.getCurrent();    }
    int getMaxHealth()      const { return hp.getBase();       }
    bool getHasFainted()    const { return hp.getHasFainted(); }
    
    static int getBaseLevel() { return base_level; }
    static int getMaxLevel()  { return max_level;  }

    // Mutator
    void reduceHealth(int amount) { hp.reduceCurrent(amount); }

    // Methods    
    virtual void revive() = 0;
    virtual void update() = 0;

    virtual void printDetailed()       const;
    virtual void printBaseStatistics() const;
    virtual void printBattle()         const = 0;
};