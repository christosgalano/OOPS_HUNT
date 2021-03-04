#pragma once
#include "Merchandise/Merchandise.hpp"

/// Abstract class that represents an item ///

class Item : public Merchandise {
protected:
    virtual void adjustStatistic(int level) = 0;

public:
    // Constructor - Destructor
    Item(const std::string& in_name, int in_price, int in_minimum_level);
    virtual ~Item() {}

    // Methods
    void adjust(int level) override {
        Merchandise::adjust(level);
        adjustStatistic(level);
    }

    void printPlain() const override;
};


/// Child classes:                                                                     ///
/// Each child class has a static constexpr int growth_factor that is used to adjust   ///
/// the stat that the item enhances. In this way the items can scale smoothly with the ///
/// heroes levels.                                                                     ///

class Weapon : public Item {
private:
    int damage;
    int hands_required;
    const int initial_damage;
    static constexpr double growth_factor {0.45};

    void adjustStatistic(int level) override { 
        damage = initial_damage * level * growth_factor; 
    }

public:
    // Constructor
    Weapon(const std::string& in_name, int in_price, int in_min_level, int in_damage, int in_hands_required)
        : Item(in_name, in_price, in_min_level), damage(in_damage), hands_required(in_hands_required),
          initial_damage(in_damage) {}

    // Accessors
    int getDamage()        const { return damage;         }
    int getHandsRequired() const { return hands_required; }

    // Methods
    void printDetailed()   const override;
    void printStatistics() const override;
};


class Armor : public Item {
private:
    int reduced_damage;
    const int initial_reduction;
    static constexpr double growth_factor {0.40};
    
    void adjustStatistic(int level) override { 
        reduced_damage = initial_reduction * level * growth_factor;
    }

public:
    // Constructor
    Armor(const std::string& in_name, int in_price, int in_min_level, int in_reduced_damage)
        : Item(in_name, in_price, in_min_level), reduced_damage(in_reduced_damage),
          initial_reduction(in_reduced_damage) {}    

    // Accessor
    int getReducedDamage() const { return reduced_damage; }    

    // Methods
    void printDetailed() const override;
    void printStatistics() const override;
};


class Potion : public Item {
private:
    int statistic_increment;
    const int initial_increment;
    static constexpr double growth_factor {0.35};

    void adjustStatistic(int level) override { 
        statistic_increment = initial_increment * level * growth_factor; 
    }

public:
    // Constructor
    Potion(const std::string& in_name, int in_price, int in_min_level, int in_statistic_increment)
        : Item(in_name, in_price, in_min_level), statistic_increment(in_statistic_increment), 
          initial_increment(in_statistic_increment) {}    

    // Accessors
    int getStatisticIncrement() const { return statistic_increment; }

    // Methods
    void printDetailed() const override;
    void printStatistics() const override;
};