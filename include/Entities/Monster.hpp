#pragma once
#include "Entities/Living.hpp"
#include "Attributes/MonsterAttributes.hpp"

class Hero; // Forward declaration

/// Abstract class that represents a monster ///

class Monster : public Living {
protected:
    // Attributes
    DamageRange damage_range;
    Defense defense;
    Dodge dodge;

    // Data regarding the effects of a spell under of which the monster may have been put
    int rounds_of_damage_reduction_required  {};
    int rounds_of_defense_reduction_required {};
    int rounds_of_dodge_reduction_required   {};

    int rounds_of_damage_reduction_passed  {};
    int rounds_of_defense_reduction_passed {};
    int rounds_of_dodge_reduction_passed   {};

    bool underIceSpell      {false};
    bool underFireSpell     {false};
    bool underLightingSpell {false};
 
    // Battle related methods
    int calculateAttackDamage();
    double calculateChanceToMissAttack(Hero* hero);

public:
    // Constructor - Destructor
    Monster(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge);
    virtual ~Monster() = 0;

    // Accessors
    int getDamageRange()       const { return damage_range.getCurrent(); }
    int getDefense()           const { return defense.getCurrent();      }
    int getChanceToDodge()     const { return dodge.getCurrent();        }
    int getMaxChanceToDodge()  const { return dodge.getMaxDodge();       }

    bool getUnderIceSpell()      const { return underIceSpell;      }
    bool getUnderFireSpell()     const { return underFireSpell;     }
    bool getUnderLightingSpell() const { return underLightingSpell; }

    // Mutators
    void reduceDamageRange(int amount, int no_rounds);
    void reduceDefense(int amount, int no_rounds);
    void reduceChanceToDodge(int amount, int no_rounds);

    // General Methods
    void adjust(int distance);
    void revive() override { hp.reviveFull(); }

    // Battle methods
    void attack(Hero* hero);
    void update() override;

    // Print methods
    void printBattle()         const override;
    void printDetailed()       const override;
    void printBaseStatistics() const override;
};