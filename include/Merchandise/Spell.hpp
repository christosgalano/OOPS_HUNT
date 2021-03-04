#pragma once
#include "Merchandise/Merchandise.hpp"

class Monster; // Forward declaration


/// Abstract class that represents a spell ///

class Spell : public Merchandise {
protected:
    int damage_range;
    int mana_required;
    int rounds_of_effect;
    const int initial_mana_required;

    void adjustManaRequired(int level) { 
        mana_required = initial_mana_required + level; 
    }
    
public:
    // Constructor - Destructor
    Spell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range, int in_mana_required, int no_rounds);
    virtual ~Spell() {}

    // Accessors
    int getDamageRange()     const { return damage_range;     }
    int getManaRequired()    const { return mana_required;    }
    int getRoundsOfEffect()  const { return rounds_of_effect; }
    
    // Methods
    void adjust(int level) override {
        Merchandise::adjust(level);
        adjustManaRequired(level);
    }

    virtual void reduceMonsterStat(Monster* m) = 0;
    void printPlain() const override;
};


/// Child classes:                                                                                           ///
/// - IceSpell      : reduces the monster's damage_range by damage_reduction % for rounds_of_effect rounds   /// 
/// - FireSpell     : reduces the monster's defense by defense_reduction % for rounds_of_effect rounds       ///
/// - LightingSpell : reduces the monster's dodge by dodge_reduction % for rounds_of_effect rounds           ///

class IceSpell : public Spell {
private:
    double damage_reduction;
public:
    // Constructor
    IceSpell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range,
             int in_mana_required, int no_rounds, double in_damage_reduction);

    // Methods
    void reduceMonsterStat(Monster* m) override;
    void printDetailed()   const override;
    void printStatistics() const override;
};


class FireSpell : public Spell {
private:
    double defense_reduction;
public:
    // Constructor
    FireSpell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range,
              int in_mana_required, int no_rounds, double in_defense_reduction);

    // Methods
    void reduceMonsterStat(Monster* m) override;
    void printDetailed()   const override;
    void printStatistics() const override;
};


class LightingSpell : public Spell {
private:
    double dodge_reduction;
public:
    // Constructor
    LightingSpell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range,
                  int in_mana_required, int no_rounds, double in_dodge_reduction);

    // Methods
    void reduceMonsterStat(Monster* m) override;
    void printDetailed()   const override;
    void printStatistics() const override;
};