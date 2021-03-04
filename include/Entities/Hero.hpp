#pragma once
#include "Entities/Living.hpp"
#include "Attributes/HeroAttributes.hpp"
#include "Merchandise/Item.hpp"
#include "Merchandise/Spell.hpp"
#include <vector>

class Monster;  // Forward declaration - we include the header file in the .cpp file

/// Abstract class that represents a hero ///

class Hero : public Living {    
protected:
    // Attributes
    Mana mana;
    Strength strength;
    Dexterity dexterity;
    Agility agility;    

    // Current money, experience and no_merchandise in possesion - initialized to 0
    int money      {};
    int experience {};
    int no_items   {};
    int no_spells  {};

    // Capacities (they increase by one every time the hero reaches a level which is a multiple of capacity_factor)
    int weapons_capacity {4};
    int armors_capacity  {2};
    int potions_capacity {3};
    int spells_capacity  {3};
    static constexpr int capacity_factor {5};

    // Items and spells in possesion
    std::vector<Weapon*> weapons;
    std::vector<Armor*> armors;
    std::vector<Potion*> potions;
    std::vector<Spell*> spells;

    // Items currently used - initialized to nullptr
    Weapon* weapon_in_right_hand {};
    Weapon* weapon_in_left_hand  {};
    Armor*  armor_in_use         {};
    Potion* potion_in_use        {};
    
    // Battle related data/methods
    int calculateAttackDamage();
    int calculateSpellDamage(Spell* s);
    double calculateChanceToMissAttack(Monster* monster);
    double calculateChanceToMissSpell(Monster* monster);

    // Percentage of dexterity we take into account regarding the chance that the hero will land the spell
    static constexpr double dex_factor {0.135};
    
    // Level related data/methods
    void calculateExperienceLimit();
    void calculateAmountOfExperienceAndMoney(Monster* monster, bool participated);
    bool levelUp();

    int experience_limit {};   // Amount of experience the hero must have in order to level up

    // exponent and base_xp are used to calculate the experience_limit
    static constexpr double exponent {1.5};   
    static constexpr int base_xp {50};

public:
    // Constructor - Destructor
    Hero(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility);
    virtual ~Hero();

    // Accessors
    int getAgility()     const { return agility.getCurrent(); }
    int getBaseAgility() const { return agility.getBase();    }

    int getMoney()     const { return money;          }
    int getNoItems()   const { return no_items;       }
    int getNoSpells()  const { return no_spells;      }
    int getNoWeapons() const { return weapons.size(); }
    int getNoArmors()  const { return armors.size();  }
    int getNoPotions() const { return potions.size(); }

    bool hasPotionInUse()    const { return (!potion_in_use) ? true : false; }
    Potion* getPotionInUse() const { return potion_in_use; }
    Armor* getArmorInUse()   const { return armor_in_use;  }

    // Mutators
    void setMoney(int amount)       { money = amount;      }
    void setExperience(int amount)  { experience = amount; }
    
    void setWeapon(Weapon* weapon);
    void equip(Armor* armor);     
    
    void use(int index);     // Only one potion can be in use each time
    void undoPotionInUse();

    // General Methods
    void revive() override {
        hp.reviveHalf(); 
        mana.setCurrentAsBase(); 
    }

    void rest() {   // Simply regenerates the full amount of hero's health and mana
        hp.setCurrentAsBase(); 
        mana.setCurrentAsBase(); 
    }
    
    // Inventory methods
    void checkInventory();
    bool buyItem(Item* item);
    bool buySpell(Spell* spell);

    Weapon* sellWeapon(int index);
    Armor* sellArmor(int index);
    Potion* sellPotion(int index);
    Spell* sellSpell(int index);

    // Battle methods
    void attack(Monster* monster);
    bool castSpell(Monster* monster, int index);
    void update() override;
    void killGains(Monster* m, bool participated);

    // Print methods
    void printWeapons()   const;
    void printArmors()    const;
    void printPotions()   const;
    void printItems()     const;
    void printSpells()    const;
    void printInventory() const;
    void printBattle()         const override;
    void printDetailed()       const override;
    void printBaseStatistics() const override;
};