#include "Entities/Hero.hpp"
#include "Entities/Monster.hpp"
#include "Utilities/ColouredLogger.hpp"
#include "Utilities/Inputter.hpp"
#include "Utilities/Random.hpp"

/// Constructor - Destructor ///
Hero::Hero(const std::string& in_name, int in_health, int in_mana, int in_strength, int in_dexterity, int in_agility)
    : Living(in_name, in_health), mana(in_mana), strength(in_strength), dexterity(in_dexterity), agility(in_agility) {}

Hero::~Hero() {
    for (Weapon* w : weapons)
        delete w;

    for (Armor* a : armors)
        delete a;

    for (Potion* p : potions)
        delete p;

    for (Spell* spell : spells)
        delete spell;

    weapons.clear();
    armors.clear();
    potions.clear();
    spells.clear();

    weapon_in_left_hand  = nullptr;
    weapon_in_right_hand = nullptr;
    armor_in_use         = nullptr;
    potion_in_use        = nullptr;
}



///// Inventory methods ///////////////////////////////////////////////////////////

void Hero::checkInventory() {
    if (!no_items) {    
        printInventory();
        return;    
    }

    std::string temp = name + "'s Inventory\n";
    ColouredLogger::LogMessageColoured(temp, ColouredLogger::Colour::GREEN);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::GREEN);
    std::string answer = Inputter::GetInput("\nDo you wish to check the hero's inventory (yes / no): ", "yes", "no");

    while (answer == "yes") {
        system("clear");
        printInventory();
        std::string choice = Inputter::GetInput("Do you wish to use any of the above (yes / no): ", "yes", "no");

        if (choice == "yes") {
            std::string category = Inputter::GetInput("Which category (weapon / armor / potion / exit): ", "weapon", "armor", "potion", "exit");
            while (category != "exit") {
                if (category == "weapon") {
                    printWeapons();
                    int no_weapons =  getNoWeapons();
                    if (no_weapons) {
                        int chosen_weapon = Inputter::GetInput("Choose based on index: ", 1, no_weapons);
                        setWeapon(weapons[chosen_weapon - 1]);
                        ColouredLogger::ignoreLine();
                        break;
                    }        
                }
                else if (category == "armor") {
                    printArmors();
                    int no_armors =  getNoArmors();
                    if (no_armors) {
                        int chosen_armor = Inputter::GetInput("Choose based on index: ", 1, no_armors);
                        equip(armors[chosen_armor - 1]);
                        ColouredLogger::ignoreLine();
                        break;
                    }
                }
                else {
                    if (potion_in_use)
                        std::cout << "Hero is already using a potion\n"; 
                    else {
                        printPotions();
                        int no_potions =  getNoPotions();
                        if (no_potions) {
                            int chosen_potion = Inputter::GetInput("Choose based on index: ", 1, no_potions);
                            use(chosen_potion - 1);
                            ColouredLogger::ignoreLine();
                            break;
                        }
                    }
                }
                category = Inputter::GetInput("Which category (weapon / armor / potion / exit): ", "weapon", "armor", "potion", "exit");
            }
        }
        answer = Inputter::GetInput("\nDo you wish to continue checking the hero's inventory (yes / no): ", "yes", "no");
    }
}

void Hero::setWeapon(Weapon* weapon) {
    if (weapon == weapon_in_right_hand && weapon == weapon_in_left_hand)
        std::cout << "Weapon is already being held by both hands.\n";
    else if (weapon == weapon_in_left_hand)
        std::cout << "Weapon is already being held by the left hand.\n";
    else if (weapon == weapon_in_right_hand)
        std::cout << "Weapon is already being held by the right hand.\n";
    else {
        std::string hand;
        if (weapon->getHandsRequired() == 2) {
            std::cout << "Weapon requires both hands...\n";
            hand = "both";
        }
        else 
            hand = Inputter::GetInput("Choose hand to hold it (left / right): ", "left", "right");

        if (hand  == "both") {
            weapon_in_left_hand = weapon;
            weapon_in_right_hand = weapon;
        }
        else if (hand == "left")
            weapon_in_left_hand = weapon;
        else 
            weapon_in_right_hand = weapon;

        std::cout << "Weapon successfully set!\n";
    }
}

void Hero::equip(Armor* armor) {
    if (armor_in_use == armor) {
        std::cout << "Armor already equiped.\n";
        return;
    }
    armor_in_use = armor;    
    std::cout << "Armor successfully equiped!\n";
}

void Hero::use(int index) {
    // We use the potion at the specific index and then we erase it from the potions vector.
    // Since we use it we know that potion_in_use = potions[index] and so we will have no 
    // memory leak, because the potion_in_use will be deleted when it is used in battle.
    // The player cannot sell the potion_in_use !
    
    Potion* potion = potions[index]; 
    std::cout << "Use potion (duration 1 battle round) to increase:\n";
    std::cout << "1. Strength\n";
    std::cout << "2. Dexterity\n";
    std::cout << "3. Agility\n";
    int choice = Inputter::GetInput("Choose attribute to increase based on index: ", 1, 3);
    int increment = potion->getStatisticIncrement();
    if (choice == 1)        strength.increaseCurrent(increment);
    else if (choice == 2)   dexterity.increaseCurrent(increment);
    else                    agility.increaseCurrent(increment);
    
    potion_in_use = potion;
    potions.erase(potions.begin() + index);
    --no_items;
    std::cout << "Potion successfully used!\n";
}

void Hero::undoPotionInUse() {
    // Used to terminate the effects of a potion after a battle round has passed.
    // It is required that the potion effect has been used. For example if the hero
    // is attacking and the potion increases their agility then its effect won't be undone
    // at the end of that round.

    // We know only one of the attributes has increased due to the potion's effect 
    strength.setCurrentAsBase();
    dexterity.setCurrentAsBase();
    agility.setCurrentAsBase();

    std::cout << potion_in_use->getName() << " effect wore off.\n";  
    delete potion_in_use;
    potion_in_use = nullptr;
}


///////////////////////////////////////////////////////////////////////////////////



///// Buy/Sell methods   //////////////////////////////////////////////////////////


// Buying methods check if some conditions are met and if they are //
// they add the item/spell to the according vector.                //

bool Hero::buyItem(Item* item) {
    if (money < item->getPrice()) {
        std::cout << "Not enough money ... ";
        return false;
    }
    if (level < item->getMinimumLevel()) {
        std::cout << "Not enough level ... ";
        return false;        
    }

    Weapon* weapon = dynamic_cast<Weapon*>(item);
    if (weapon) {
        if (weapons_capacity == getNoWeapons()) {
            std::cout << "Not enough weapons capacity ... ";
            return false;
        }
        weapons.push_back(weapon);
    }
    else {
        Armor* armor = dynamic_cast<Armor*>(item);
        if (armor) {
            if (armors_capacity == getNoArmors()) {
                std::cout << "Not enough armors capacity ... ";
                return false;
            }
            armors.push_back(armor);
        }
        else {
            Potion* potion = dynamic_cast<Potion*>(item);
            if (potions_capacity == getNoPotions()) {
                std::cout << "Not enough potions capacity ... ";
                return false;
            }
            potions.push_back(potion);
        }
    }

    ++no_items;
    money -=  item->getPrice();
    return true;
}

bool Hero::buySpell(Spell* spell) {
    if (money < spell->getPrice()) {
        std::cout << "Not enough money ... ";
        return false;
    }
    if (level < spell->getMinimumLevel()) {
        std::cout << "Not enough level ... ";
        return false;        
    }
    if (spells_capacity == no_spells) {
        std::cout << "Not enought spells capacity ... ";
        return false;
    }

    spells.push_back(spell);
    ++no_spells;
    money -= spell->getPrice();
    return true;
}

// Selling methods erase the item/spell the player wants to sell from the //
// acording vector and then return a pointer to that item/spell.          //

Weapon* Hero::sellWeapon(int index) {
    Weapon* weapon = weapons[index];
    if (weapon == weapon_in_left_hand)
        weapon_in_left_hand = nullptr;
    if (weapon == weapon_in_right_hand)
        weapon_in_right_hand = nullptr;
    money += weapon->getPrice() / 2;
    weapons.erase(weapons.begin() + index);  
    --no_items;
    std::cout << "Weapon successfully sold!\n";
    return weapon;
}

Armor* Hero::sellArmor(int index) {
    Armor* armor = armors[index];
    if (armor == armor_in_use)
        armor_in_use = nullptr;
    money += armor->getPrice() / 2;
    armors.erase(armors.begin() + index);
    --no_items;
    std::cout << "Armor successfully sold!\n";
    return armor;
}

Potion* Hero::sellPotion(int index) {
    // We have ensured that the potion the player tries to sell is
    // not the one in use, because when we use a potion we erase it
    // from the potions vector and so it would not appear as a viable
    // option for sale.

    Potion* potion = potions[index];    
    money += potion->getPrice() / 2;
    potions.erase(potions.begin() + index); 
    --no_items; 
    std::cout << "Potion successfully sold!\n";
    return potion;  
}

Spell* Hero::sellSpell(int index) {
    Spell* spell = spells[index];
    money += spell->getPrice() / 2;
    spells.erase(spells.begin() + index);
    --no_items;
    std::cout << "Spell successfully sold!\n";
    return spell;
}

///////////////////////////////////////////////////////////////////////////////////



///// Battle methods     //////////////////////////////////////////////////////////

double Hero::calculateChanceToMissAttack(Monster* monster) {
    // Hero's miss is the same as monster's dodge.
    return monster->getChanceToDodge();
}

int Hero::calculateAttackDamage() {
    // If the hero has no weapons then he will only deal as much damage as their strength.
    // Otherwise the damage of their weapons will be added to the their damage_to_deal. 
    // We don't take into consideration here the monster's defense.

    int damage_to_deal = strength.getCurrent();
    if (weapon_in_left_hand)
        damage_to_deal += weapon_in_left_hand->getDamage();
    if (weapon_in_right_hand)
        damage_to_deal += weapon_in_right_hand->getDamage();
    if (weapon_in_right_hand && (weapon_in_right_hand == weapon_in_left_hand))  // If weapon requires both hands
        damage_to_deal -= weapon_in_right_hand->getDamage();

    // If the hero is using a potion to increase their strength, then the effect of it has already taken
    // place so we can call undoPotionInUse(), since a potion can only be used once and it has a duration of
    // one battle round.
    if (strength.getCurrent() != strength.getBase())
        undoPotionInUse();

    return damage_to_deal;
}


void Hero::attack(Monster* monster) {
    // The greater the chance_to_miss the more likely it will will belong in [1.0, 100.0).
    RandomDouble rnd {1.0, 100.0};
    if (calculateChanceToMissAttack(monster) >= rnd()) {
        std::cout << monster->getName() << " dodged " << name << "'s attack\n";
        return;
    }

    // If the hero lands the attack then the damage that will be dealt is their attack_damage - monster's defense.
    // If the hero's attack_damage is less than monster's defense then their attack will deal a trivial amount of damage (minimum_damage).
    int damage = calculateAttackDamage();
    damage -= monster->getDefense();

    int minimum_damage = monster->getMaxHealth() * minimum_damage_factor;
    if (damage < minimum_damage)
        damage = minimum_damage;

    std::cout << name << "'s attack dealt ";
    ColouredLogger::LogMessageColoured(std::to_string(damage), ColouredLogger::RED);
    std::cout << " damage to " << monster->getName() << '\n';
    monster->reduceHealth(damage);

    if (monster->getHasFainted())
        std::cout << monster->getName() << " has fainted...\n";
}


double Hero::calculateChanceToMissSpell(Monster* monster) {
    // Hero's miss is the same as monster's dodge.
    // When a hero casts a spell we take into consideration their dexterity.
    // The higher the hero's dexterity "the smaller" the propability the monster will dodge the spell.

    double chance_to_miss = monster->getChanceToDodge() - dexterity.getCurrent() * dex_factor;
    if (chance_to_miss < 0)
        chance_to_miss = 0;

    return chance_to_miss;
}   

int Hero::calculateSpellDamage(Spell* s) {
    // When the hero casts a spell we calculate the damage it will deal taking into consideration
    // their dexterity by a factor of dex_factor %.
    // We can utilize the foul damage range of spell all the time, only an amount that
    // belongs in [damage_range * 0.65, damage_range].

    RandomInt rnd {static_cast<int>(s->getDamageRange() * 0.65), s->getDamageRange()};

    int damage_to_deal = rnd() * dexterity.getCurrent() * dex_factor;

    // If the hero is using a potion to increase their dexterity, then the effect of it has already
    // taken place since we call first calculateChanceToMissSpell() and then calculateSpellDamage().
    if (dexterity.getCurrent() != dexterity.getBase())
        undoPotionInUse();

    return damage_to_deal;
}


/// A hero can cast any kind of spell they wish towards a monster, but if that specific monster is already under a spell of the same  ///
/// type with the the one the hero is about to cast, then the second spell will only deal damage and not change the effects of the    ///
/// first one. For example let's consider that a hero casts an IceSpell towards a monster that reduces its damage_range by 20% and    ///
/// lasts for 2 rounds. If the same hero attempts to cast another IceSpell towards that specific monster at the next round, then that ///
/// spell will only deal damage and it won't change the damage_reduction (20%) of the first spell nor will it increase the rounds of  ///
/// effect (2). Conclusively, a spell always deals damage but only reduces a certain statistic of a monster for x rounds if no other  ///
/// spell of the same kind already affects that specific monster.                                                                     ///

bool Hero::castSpell(Monster* monster, int index) {
    Spell* s = spells[index];
    if (mana.getCurrent() < s->getManaRequired()) {
        std::cout << "Not enough magic power. You need " << s->getManaRequired()  << " to cast this spell";
        std::cout << ", and you currently have " << mana.getCurrent() << '\n';
        return false;
    }

    // The greater the chance_to_miss the more likely it will will belong in [1.0, 100.0).
    RandomDouble rnd {1.0, 100.0};
    if (calculateChanceToMissAttack(monster) >= rnd()) {
        std::cout << monster->getName() << " dodged the spell\n";
        return true;
    }

    s->reduceMonsterStat(monster);

    int damage = calculateSpellDamage(s);
    damage -= monster->getDefense();

    int minimum_damage = monster->getMaxHealth() * minimum_damage_factor;
    if (damage < minimum_damage)
        damage = minimum_damage;

    std::cout << name << "'s spell dealt ";
    ColouredLogger::LogMessageColoured(std::to_string(damage), ColouredLogger::RED);
    std::cout << " damage to " << monster->getName() << '\n';

    monster->reduceHealth(damage);
    
    if (monster->getHasFainted())
        std::cout << monster->getName() << " has fainted...\n";

    spells.erase(spells.begin() + index);
    --no_spells;
    delete s;

    return true;
}

void Hero::update() {
    // We simply regenarate a certain amount of the hero's health and mana,
    // if they are not both full and the hero is not dead.
    if (getHasFainted()) return;

    if (hp.getCurrent() != hp.getBase()) {
        std::cout << name;
        hp.regenerateHealth();
    }

    if (mana.getCurrent() != mana.getBase()) {
        std::cout << name;
        mana.regenerateMana();
    }
}

void Hero::killGains(Monster* m, bool participated) {
    calculateAmountOfExperienceAndMoney(m, participated);
    levelUp();
}

///////////////////////////////////////////////////////////////////////////////////


/////  Print methods  /////////////////////////////////////////////////////////////

void Hero::printWeapons() const {
    if (!weapons.size()) {
        std::cout << name << " has no weapons.\n";
        return;
    }

    int index = 1;
    std::cout << name << "'s weapons:\n";
    for (const Weapon* w : weapons) {
        std::cout << index << ". ";
        w->printDetailed();
        ++index;
    }
}

void Hero::printArmors() const {
    if (!armors.size()) {
        std::cout << name << " has no armors.\n";
        return;
    }

    int index = 1;
    std::cout << name << "'s armors:\n";
    for (const Armor* a : armors) {
        std::cout << index << ". ";
        a->printDetailed();
        ++index;
    }
}

void Hero::printPotions() const {
    if (!potions.size()) {
        std::cout << name <<  "has no potions.\n";
        return;
    }

    int index = 1;
    std::cout << name << "'s potions:\n";
    for (const Potion* p : potions) {
        std::cout << index << ". ";
        p->printDetailed();
        ++index;
    }
}

void Hero::printItems() const {
    for (const Weapon* w : weapons) {
        std::cout << "- ";
        w->printDetailed();
    }
    for (const Armor* a : armors) {
        std::cout << "- ";
        a->printDetailed();
    }
    for (const Potion* p : potions) {
        std::cout << "- ";
        p->printDetailed();
    }
}

void Hero::printSpells() const {
    if (!no_spells) {
        std::cout << name << " has no spells.\n";
        return;
    }

    int index = 1;
    std::cout << name << "'s spells:\n";
    for (const Spell* s : spells) {
        std::cout << index << ". ";
        s->printDetailed();
        ++index;
    }   
}

void Hero::printInventory() const {
    std::string temp = name + "'s Inventory\n";
    ColouredLogger::LogMessageColoured(temp, ColouredLogger::Colour::GREEN);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::GREEN);
        
    if (no_items) {
        std::cout << "Consists of :\n";
        printItems();
    } 
    else {
        std::cout << name << "'s inventory is empty\n";
        return;
    }

    std::cout << '\n' << name << " is currently:\n";

    if (!weapon_in_right_hand && !weapon_in_left_hand)
        std::cout << "- holding no weapon\n";
    else if (!weapon_in_left_hand && weapon_in_right_hand)
        std::cout << "- holding " << weapon_in_right_hand->getName() << " with the right hand\n";
    else if (!weapon_in_right_hand && weapon_in_left_hand)
        std::cout << "- holding " << weapon_in_left_hand->getName() << " with the left hand\n";
    else {
        if (weapon_in_left_hand == weapon_in_right_hand)
            std::cout << "- holding " << weapon_in_left_hand->getName() << " with both hands\n";
        else {
            std::cout << "- holding " << weapon_in_right_hand->getName() << " with the right hand and a ";
            std::cout << weapon_in_left_hand->getName() << " with the left hand\n";
        }
    }

    if (!armor_in_use)
        std::cout << "- wearing no armor\n";
    else 
        std::cout << "- wearing " << armor_in_use->getName() << '\n';

    if (!potion_in_use)
        std::cout << "- using no potion\n";
    else 
        std::cout << "- using " << potion_in_use->getName() << '\n';

    std::cout << std::flush;
}

void Hero::printBattle() const {
    std::string temp = name + '\n';
    ColouredLogger::LogMessageColoured(temp, ColouredLogger::CYAN);
    std::cout << "- Health: "    << hp.getCurrent()         << '\n';
    std::cout << "- Mana: "     << mana.getCurrent()       << '\n';
    std::cout << "- Strength: "  << strength.getCurrent()   << '\n';
    std::cout << "- Dexterity: " << dexterity.getCurrent()  << '\n';
    std::cout << "- Agility: "   << agility.getCurrent()    << '\n';
}

void Hero::printDetailed() const {
    Living::printDetailed();
    std::cout << "- Mana: "       << mana.getCurrent()       << '\n';
    std::cout << "- Strength: "   << strength.getCurrent()   << '\n';
    std::cout << "- Dexterity: "  << dexterity.getCurrent()  << '\n';
    std::cout << "- Agility: "    << agility.getCurrent()    << '\n';
    std::cout << "- Money: "      << money                   << '\n';
    std::cout << "- Experience: " << experience              << std::endl;
}

void Hero::printBaseStatistics() const {
    Living::printBaseStatistics();
    std::cout << "- Base Mana: "      << mana.getBase()       << '\n';
    std::cout << "- Base Strength: "  << strength.getBase()   << '\n';
    std::cout << "- Base Dexterity: " << dexterity.getBase()  << '\n';
    std::cout << "- Base Agility: "   << agility.getBase()    << std::endl;  
}

///////////////////////////////////////////////////////////////////////////////////



/////  Level methods  /////////////////////////////////////////////////////////////

void Hero::calculateExperienceLimit() {
    // Formula to calculate experience required to level up.
    experience_limit = floor(base_xp * pow(level, exponent));
}

void Hero::calculateAmountOfExperienceAndMoney(Monster* monster, bool participated) {
    // Money and experience gained from a kill are calculated based on the monster's level
    // as well as on the level difference between the hero and the monster.
    // If the hero did not participate in the monster's killing (participated == false),
    // then they gain half of the experience and half of the money.

    int monster_level = monster->getLevel();
    int difference = abs(level - monster_level);
    calculateExperienceLimit();                        
    
    int exp_to_earn = 0;
    int money_to_earn = 0;
    
    if (level - monster_level >= 3) 
        exp_to_earn += experience_limit * 0.20;
    else if (level - monster_level >= 2)
        exp_to_earn += experience_limit * 0.30;
    else if (difference == 0 || difference == 1)
        exp_to_earn += experience_limit * 0.45;
    else if (monster_level - level >= 3)
        exp_to_earn += experience_limit * 1.15;
    else if (monster_level - level >= 2)
        exp_to_earn += experience_limit * 0.75;

    if (monster_level <= 5)
        money_to_earn += monster_level * 3;
    else if (monster_level <= 10)
        money_to_earn += monster_level * 4;
    else if (monster_level <= 25)
        money_to_earn += monster_level * 5;
    else if (monster_level <= 50)
        money_to_earn += monster_level * 6;
    else 
        money_to_earn += monster_level * 7;
    
    if (!participated) {
        exp_to_earn   /= 2;
        money_to_earn /= 2;
    }

    money += money_to_earn;
    experience += exp_to_earn;

    std::cout << name << " was awarded with " << exp_to_earn << " exp and " << money_to_earn;
    std::cout << " gold for the killing of " << monster->getName() << '\n';
}

bool Hero::levelUp() {
    // Base class virtual method.
    // It's called by the derived one's every time the hero levels up.
    if (level == max_level) {
        std::cout << name << " has reached the maximum level...\n";
        return false;
    }

    // A hero levels up when experience >= experience_limit * level.
    // We have already calculated the experience_limit in calculateAmountOfExperienceAndMoney(),
    // which is called before this function ( see HeroTypes killGains() ).
    if (experience < experience_limit)
        return false;

    // The higher the level of the hero the more experience is required for them to level up.
    ++level;

    if (level % capacity_factor == 0) {  // Check if we need to update the capacities
        ++weapons_capacity;
        ++armors_capacity;
        ++potions_capacity;
        ++spells_capacity;
    }

    experience = experience - experience_limit;

    // We simply upgrade the attributes ... That is the advantage of using
    // an Attribute class to represent an attribute instead of having multiple
    // int variables in our hero class.
    hp.upgrade(level);
    mana.upgrade(level);
    strength.upgrade(level);
    dexterity.upgrade(level);
    agility.upgrade(level);

    return true;
}

///////////////////////////////////////////////////////////////////////////////////