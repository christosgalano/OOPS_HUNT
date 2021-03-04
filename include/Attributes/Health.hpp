#pragma once
#include "Attributes/Attribute.hpp"

/// Class that represents the health regarding attribute of a living being ///

class Health : public Attribute {   
private:
    bool has_fainted {false};   
    
    // At the end of each battle round a living being regenerates health_factor % of its health
    static constexpr double health_factor {0.10};

public:
    // Constructor
    Health(int in_hp) : Attribute(in_hp) {}

    // Accessor
    bool getHasFainted() const { return has_fainted; }

    // Methods
    void reduceCurrent(int amount) override{
        Attribute::reduceCurrent(amount);
        if (current_stat <= 0)
            has_fainted = true;
    }

    void regenerateHealth() {
        if (current_stat == base_stat)  return;
        
        int amount = static_cast<int>(base_stat * health_factor);

        if (current_stat + amount > base_stat) {
            std::cout << " just regenarated " << base_stat - current_stat << " health\n";       
            current_stat = base_stat;
        }
        else {
            std::cout << " just regenarated " << amount << " health\n";
            current_stat += amount;
        }
    }

    void reviveFull() { 
        current_stat = base_stat;
        has_fainted = false; 
    }

    void reviveHalf() {
        current_stat = base_stat / 2;
        has_fainted = false;
    }

    void upgrade(int level) override {
        // The hero's base_hp increases but we keep the current_hp equal to the difference new_base_hp - diff,
        // where diff is the difference between base_hp and current_hp that existed before we upgraded the first one.
        // The process is similar for Mana ...
        int diff = base_stat - current_stat;
        base_stat = floor( (.8 + level / 100) * level * ((upper_bound - lower_bound) / 275.222) + lower_bound + .1 );
        current_stat = base_stat - diff;
    }
};
