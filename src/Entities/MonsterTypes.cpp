#include "Entities/MonsterTypes.hpp"

/// Just as with the Hero class, we must set the upper bounds to the attributes to specific values in order for ///
//  them to be able to upgrade normally according to the monster's current level ...                            /// 
/// Each type of Monster has different upper_bounds for each attribute ...                                      ///
/// Specifically:                                                                                               ///
/// - Dragon's damage_range is more enhanced compared to the other attributes                                   ///
/// - Exoskeleton's defense is more enhanced compared to the other attributes                                   ///
/// - Spirit's dodge is more enhanced compared to the other attributes                                          ///     

Dragon::Dragon(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge)
    : Monster(in_name, in_health, in_damage_range, in_defense, in_chance_to_dodge)
{
    hp.setUpperBound(2000);
    damage_range.setUpperBound(1000);
    defense.setUpperBound(400);
    dodge.setUpperBound(300);    
}

void Dragon::printDetailed() const {
    std::cout << "Dragon ";
    Monster::printDetailed();
}


Exoskeleton::Exoskeleton(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge)
    : Monster(in_name, in_health, in_damage_range, in_defense, in_chance_to_dodge)
{
    hp.setUpperBound(2000);
    damage_range.setUpperBound(300);
    defense.setUpperBound(600);
    dodge.setUpperBound(100);
}

void Exoskeleton::printDetailed() const {
    std::cout << "Exoskeleton ";
    Monster::printDetailed();
}


Spirit::Spirit(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge)
    : Monster(in_name, in_health, in_damage_range, in_defense, in_chance_to_dodge)
{
    hp.setUpperBound(1500);
    damage_range.setUpperBound(800);
    defense.setUpperBound(200);
    dodge.setUpperBound(300);
}

void Spirit::printDetailed() const {
    std::cout << "Spirit ";
    Monster::printDetailed();
}