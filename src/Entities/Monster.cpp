#include "Entities/Monster.hpp"
#include "Entities/Hero.hpp"
#include "Utilities/ColouredLogger.hpp"
#include "Utilities/Random.hpp"

/// Constructor - Destructor ///
Monster::Monster(const std::string& in_name, int in_health, int in_damage_range, int in_defense, int in_chance_to_dodge)
        : Living(in_name, in_health), damage_range(in_damage_range), defense(in_defense), dodge(in_chance_to_dodge) {} 

Monster::~Monster() {}


///// Level methods     ///////////////////////////////////////////////////////////

void Monster::adjust(int new_level) {
    // We adjust the monster's attributes in order for the battle to be fair and challenging.
    // The level of the monster will depend on new_level.
    // Edge cases:
    // - If level < 1 then we set level = 1
    // - If level > max_level then we set level = max_level  

    // We just make sure the monster's health bar is full.
    hp.setCurrentAsBase();

    level = new_level;    // We just set the current level equal to new_level

    // Edge cases
    if (level < 1)          level = 1;
    if (level > max_level)  level = max_level;    

    hp.upgrade(level); // We already made sure its hp will be full
    damage_range.upgrade(level);
    defense.upgrade(level);
    dodge.upgrade(level);
}

////////////////////////////////////////////////////////////////////////////////////



///// Battle methods     ///////////////////////////////////////////////////////////

double Monster::calculateChanceToMissAttack(Hero* hero) {
    // Monster's miss is the same as hero's dodge.
    double chance_to_miss = hero->getAgility();

    // If the hero is using a potion to increase their agility, then the effect of it 
    // has already taken place.
    if (hero->getAgility() != hero->getBaseAgility())
        hero->undoPotionInUse();

    return chance_to_miss;
}

int Monster::calculateAttackDamage() {
    // A monster can deal from half up to its full damage_range amount of damage.
    int dmg_range = damage_range.getCurrent();
    RandomInt rnd {dmg_range / 2, dmg_range};
    return rnd();
}

void Monster::attack(Hero* hero) {
    // The greater the chance_to_miss the more likely it will will belong in [1.0, 100.0).
    RandomDouble rnd_c {1.0, 100.0};
    if (calculateChanceToMissAttack(hero) >= rnd_c()) {
        std::cout << hero->getName() << " dodged " << name << "'s attack\n";
        return;
    }

    // If the Monster lands the attack then the damage that will be dealt is its attack_damage - hero's armor_damage_reduction.
    // If the Monster's attack_damage is less than hero's armor_damage_reduction then its attack will deal a trivial amount of damage (minimum_damage).
    int damage = calculateAttackDamage();
    Armor* armor_in_use = hero->getArmorInUse();
    if (armor_in_use)
        damage -= armor_in_use->getReducedDamage();

    int minimum_damage = hero->getMaxHealth() * minimum_damage_factor;
    if (damage < minimum_damage)
        damage = minimum_damage;

    std::cout << name << "'s attack dealt ";
    ColouredLogger::LogMessageColoured(std::to_string(damage), ColouredLogger::RED);
    std::cout << " damage to " << hero->getName() << '\n';
    hero->reduceHealth(damage);

    if (hero->getHasFainted()) 
        std::cout << hero->getName() << " has fainted...\n";
}

void Monster::update() {
    // If the monster is under the effect of a spell and the required amount of rounds have
    // passed, then we undo the effect. We also regenarate a certain amount of the monster's health.
    if (underIceSpell && ++rounds_of_damage_reduction_passed == rounds_of_damage_reduction_required) {
        std::cout << "IceSpell's effect wore off\n";
        underIceSpell = false;
        rounds_of_damage_reduction_passed = 0;
        rounds_of_damage_reduction_required = 0;
        damage_range.setCurrentAsBase();
    } 

    if (underFireSpell && ++rounds_of_defense_reduction_passed == rounds_of_defense_reduction_required) {
        std::cout << "FireSpell's effect wore off\n";
        underFireSpell = false;
        rounds_of_defense_reduction_passed = 0;
        rounds_of_defense_reduction_required = 0;
        defense.setCurrentAsBase();
    }

    if (underLightingSpell && ++rounds_of_dodge_reduction_passed == rounds_of_dodge_reduction_required) {
        std::cout << "LightingSpell's effect wore off\n";
        underLightingSpell = false;
        rounds_of_dodge_reduction_passed = 0;
        rounds_of_dodge_reduction_required = 0;
        dodge.setCurrentAsBase();
    }

    if (hp.getCurrent() == hp.getBase()) return;
    std::cout << name;
    hp.regenerateHealth();
}

void Monster::reduceDamageRange(int amount, int no_rounds) {
    underIceSpell = true;
    damage_range.reduceCurrent(amount);
    rounds_of_damage_reduction_required = no_rounds;
}

void Monster::reduceDefense(int amount, int no_rounds) {
    underFireSpell = true;
    defense.reduceCurrent(amount);
    rounds_of_defense_reduction_required = no_rounds;
}

void Monster::reduceChanceToDodge(int amount, int no_rounds) {
    underLightingSpell = true;
    dodge.reduceCurrent(amount);
    rounds_of_dodge_reduction_required = no_rounds;
}

////////////////////////////////////////////////////////////////////////////////////



/////  Printing methods  ///////////////////////////////////////////////////////////

void Monster::printBattle() const {
    std::string temp = name + '\n';
    ColouredLogger::LogMessageColoured(temp, ColouredLogger::RED);
    std::cout << "- Health: "          << hp.getCurrent()           << '\n';
    std::cout << "- Damage range: "    << damage_range.getCurrent() << '\n';
    std::cout << "- Defense: "         << defense.getCurrent()      << '\n';
    std::cout << "- Chance to dodge: " << dodge.getCurrent()        << '\n';
}

void Monster::printDetailed() const {
    Living::printDetailed();
    std::cout << "- Damage range: "     << damage_range.getCurrent() << '\n';
    std::cout << "- Defense: "          << defense.getCurrent()      << '\n';
    std::cout << "- Chance to dodge: "  << dodge.getCurrent()        << '\n';
}

void Monster::printBaseStatistics() const {
    Living::printBaseStatistics();
    std::cout << "- Base Damage range: "     << damage_range.getBase() << '\n';
    std::cout << "- Base Defense: "          << defense.getBase()      << '\n';
    std::cout << "- Base Chance to dodge: "  << dodge.getBase()        << '\n';
}

////////////////////////////////////////////////////////////////////////////////////