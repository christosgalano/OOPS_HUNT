#include "Entities/HeroTypes.hpp"

/// We must set the upper bounds to the attributes to specific values in order for them to be able to upgrade normally ///
/// according to the hero's current level ... The attributes growth graph is roughly parabolic ...                     ///
/// Each type of Hero has different upper_bounds for each attribute ...                                                ///
/// Specifically:                                                                                                      ///
/// - Warrior's health, strength and agility grow faster than the other attributes                                     ///
/// - Sorcerer's mana, dexterity and agility grow faster than the other attributes                                     ///
/// - Paladin's health, strength and dexterity grow faster than the other attributes                                   ///            


Warrior::Warrior(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility)
        : Hero(in_name, in_health, in_mana, in_strength, in_dexterity, in_agility)
{
    hp.setUpperBound(2100);
    mana.setUpperBound(600);
    strength.setUpperBound(1000);
    dexterity.setUpperBound(500);
    agility.setUpperBound(300);
}

void Warrior::printDetailed() const {
    std::cout << "Warrior ";
    Hero::printDetailed();
}


Sorcerer::Sorcerer(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility)
        : Hero(in_name, in_health, in_mana, in_strength, in_dexterity, in_agility)
{
    hp.setUpperBound(1800);
    mana.setUpperBound(1000);
    strength.setUpperBound(400);
    dexterity.setUpperBound(1000);
    agility.setUpperBound(350);
}

void Sorcerer::printDetailed() const {
    std::cout << "Sorcerer ";
    Hero::printDetailed();
}


Paladin::Paladin(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility)
        : Hero(in_name, in_health, in_mana, in_strength, in_dexterity, in_agility)
{
    hp.setUpperBound(2000);
    mana.setUpperBound(650);
    strength.setUpperBound(900);
    dexterity.setUpperBound(900);
    agility.setUpperBound(250);   
}

void Paladin::printDetailed() const {
    std::cout << "Paladin ";
    Hero::printDetailed();
}