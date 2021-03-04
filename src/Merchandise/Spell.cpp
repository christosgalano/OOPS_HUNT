#include "Merchandise/Spell.hpp"
#include "Entities/Monster.hpp"
#include <iostream>

Spell::Spell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range, int in_mana_required, int no_rounds)
    : Merchandise(in_name, in_price, in_minimum_level), damage_range(in_damage_range), 
      mana_required(in_mana_required), rounds_of_effect(no_rounds),
      initial_mana_required(in_mana_required) {}

void Spell::printPlain() const {
    std::cout << "Spell: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level << '\n'; 
}


IceSpell::IceSpell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range,
                    int in_mana_required, int no_rounds, double in_damage_reduction)
    : Spell(in_name, in_price, in_minimum_level, in_damage_range, in_mana_required, no_rounds),
      damage_reduction(in_damage_reduction) {}

void IceSpell::reduceMonsterStat(Monster* monster) {
    if (monster->getUnderIceSpell()) {
        std::cout << monster->getName() << " is already under an IceSpell\n";
        return;
    }
    monster->reduceDamageRange(monster->getDamageRange() * damage_reduction, rounds_of_effect);
}

void IceSpell::printDetailed() const {
    std::cout << "IceSpell: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level;
    std::cout << ", Damage range: " << damage_range << ", Magic Power required: " << mana_required;
    std::cout << ", Damage reduction: " << damage_reduction << '\n';
}

void IceSpell::printStatistics() const {
    std::cout << "IceSpell: " << name << ", Damage range: " << damage_range << ", Magic Power required: " << mana_required;
    std::cout << ", Damage reduction: " << damage_reduction << '\n';
}


FireSpell::FireSpell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range,
                     int in_mana_required, int no_rounds, double in_defense_reduction)
    : Spell(in_name, in_price, in_minimum_level, in_damage_range, in_mana_required, no_rounds),
      defense_reduction(in_defense_reduction) {}

void FireSpell::reduceMonsterStat(Monster* monster) {
    if (monster->getUnderFireSpell()) {
        std::cout << monster->getName() << " is already under an FireSpell\n";
        return;
    }
    monster->reduceDefense(monster->getDefense() * defense_reduction, rounds_of_effect);
}

void FireSpell::printDetailed() const {
    std::cout << "FireSpell: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level;
    std::cout << ", Damage range: " << damage_range << ", Magic Power required: " << mana_required;
    std::cout << ", Defense reduction: " << defense_reduction << '\n';
}

void FireSpell::printStatistics() const {
    std::cout << "FireSpell: " << name << ", Damage range: " << damage_range << ", Magic Power required: " << mana_required;
    std::cout << ", Defense reduction: " << defense_reduction << '\n';
}


LightingSpell::LightingSpell(const std::string& in_name, int in_price, int in_minimum_level, int in_damage_range,
                             int in_mana_required, int no_rounds, double in_dodge_reduction)
    : Spell(in_name, in_price, in_minimum_level, in_damage_range, in_mana_required, no_rounds), 
      dodge_reduction(in_dodge_reduction) {}

void LightingSpell::reduceMonsterStat(Monster* monster) {
    if (monster->getUnderLightingSpell()) {
        std::cout << monster->getName() << " is already under an LightingSpell\n";
        return;
    }
    monster->reduceChanceToDodge(monster->getChanceToDodge() * dodge_reduction, rounds_of_effect);
}

void LightingSpell::printDetailed() const {
    std::cout << "LightingSpell: " << name << ", Price: " << price << ", MinimumLevel: " << minimum_level;
    std::cout << ", Damage range: " << damage_range << ", Magic Power required: " << mana_required;
    std::cout << ", Dodge reduction: " << dodge_reduction << '\n';
}

void LightingSpell::printStatistics() const {
    std::cout << "LightingSpell: " << name << ", Damage range: " << damage_range << ", Magic Power required: " << mana_required;
    std::cout << ", Dodge reduction: " << dodge_reduction << '\n';
}