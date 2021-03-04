#pragma once
#include "Entities/HeroTypes.hpp"
#include "Entities/MonsterTypes.hpp"
#include "Utilities/Random.hpp"

/// A class with data and methods regarding the creation of beings and merchandise ... This class   ///
/// cannot be instantiated (the constructor is deleted) and only its static methods can be used ... ///
/// Each type of Hero and Monster gets assigned certain attributes that are specifically chosen     ///
/// in order to scale well with the leveling system ... Each item's specific characteristic         ///
//  (damage, reduced_dagame, statistic_increment) value can be different from another's one ...     ///
/// For example two armors can have different reduced_damage ... The name are chosen randomly from  ///
/// a pool of names ragarding that specific type of being or merchandise ...                        ///

// All name-arrays contain 10 elements
static RandomInt rnd_name {0, 9};

class Generator {
private:
    /////  Names  //////////////////////////////////////////////////////////////
    static const std::string warrior_names[10];

    static const std::string sorcerer_names[10];

    static const std::string paladin_names[10];

    static const std::string dragon_names[10];

    static const std::string exoskeleton_name[10];

    static const std::string spirit_names[10];

    static const std::string one_hand_weapon_names[10];

    static const std::string two_hand_weapon_names[10];

    static const std::string armor_names[10];

    static const std::string potion_names[10];

    static const std::string ice_spell_names[10];

    static const std::string fire_spell_names[10];

    static const std::string lighting_spell_names[10];
    ////////////////////////////////////////////////////////////////////////////


    /////  Base statistics  ////////////////////////////////////////////////////
    // Warrior
    static constexpr int w_base_hp        {60};
    static constexpr int w_base_mana      {40};
    static constexpr int w_base_strength  {23};
    static constexpr int w_base_dexterity  {5};
    static constexpr int w_base_agility    {8};

    // Sorcerer
    static constexpr int s_base_hp        {50};
    static constexpr int s_base_mana      {60};
    static constexpr int s_base_strength  {13};
    static constexpr int s_base_dexterity {18};
    static constexpr int s_base_agility    {8};    

    // Paladin
    static constexpr int p_base_hp        {50};
    static constexpr int p_base_mana      {50};
    static constexpr int p_base_strength  {18};
    static constexpr int p_base_dexterity {13};
    static constexpr int p_base_agility    {5};  

    // Dragon
    static constexpr int d_base_hp   {50};
    static constexpr int d_dmg_range {25};
    static constexpr int d_defense    {6};
    static constexpr int d_dodge      {6};

    // Exoskeleton
    static constexpr int e_base_hp   {55};
    static constexpr int e_dmg_range {10};
    static constexpr int e_defense    {8};
    static constexpr int e_dodge      {5};

    // Spirit
    static constexpr int sp_base_hp   {40};
    static constexpr int sp_dmg_range {20};
    static constexpr int sp_defense    {5};
    static constexpr int sp_dodge     {10};

    // One Hand Weapon
    static constexpr int ohw_price         {3};
    static constexpr int ohw_minimum_level {2};
    static constexpr int ohw_damage        {6};
        
    // Two Hand Weapon
    static constexpr int thw_price          {8};
    static constexpr int thw_minimum_level  {4};
    static constexpr int thw_damage        {10};

    // Armor
    static constexpr int a_price            {5};
    static constexpr int a_minimum_level    {2};
    static constexpr int a_damage_reduction {8};

    // Potion
    static constexpr int pt_price         {3};
    static constexpr int pt_minimum_level {1};
    static constexpr int pt_increment     {3};

    // Spells
    static constexpr int max_rounds {3};

    // IceSpell
    static constexpr int i_price               {6};
    static constexpr int i_minimum_level       {3};
    static constexpr int i_dmg_range          {10};
    static constexpr int i_mana_required      {25};
    static constexpr double i_dmg_reduction {15.0};

    // FireSpell
    static constexpr int f_price                  {10};
    static constexpr int f_minimum_level           {4};
    static constexpr int f_dmg_range              {20};
    static constexpr int f_mana_required          {35};
    static constexpr double f_defense_reduction {20.0};

    // LightingSpell
    static constexpr int l_price                 {4};
    static constexpr int l_minimum_level         {2};
    static constexpr int l_dmg_range            {10};
    static constexpr int l_mana_required        {20};
    static constexpr double l_dodge_reduction {30.0};
   ////////////////////////////////////////////////////////////////////////////

public:
    Generator() = delete;

    /////  Generate functions  /////////////////////////////////////////////////
    static Warrior* generateWarrior() {
        return new Warrior(warrior_names[rnd_name()], w_base_hp, w_base_mana, w_base_strength, w_base_dexterity, w_base_agility);
    }

    static Sorcerer* generateSorcerer() {
        return new Sorcerer(sorcerer_names[rnd_name()], s_base_hp, s_base_mana, s_base_strength, s_base_dexterity, s_base_agility);
    }

    static Paladin* generatePaladin() {
        return new Paladin(paladin_names[rnd_name()], p_base_hp, p_base_mana, p_base_strength, p_base_dexterity, p_base_agility);    
    }

    static Dragon* generateDragon() {
        return new Dragon(dragon_names[rnd_name()], d_base_hp, d_dmg_range, d_defense, d_dodge);
    }

    static Exoskeleton* generateExoskeleton() {
        return new Exoskeleton(exoskeleton_name[rnd_name()], e_base_hp, e_dmg_range, e_defense, e_dodge);
    }

    static Spirit* generateSpirit() {
        return new Spirit(spirit_names[rnd_name()], sp_base_hp, sp_dmg_range, sp_defense, sp_dodge);
    }

    static Weapon* generateOneHandWeapon() {
        RandomInt rnd_dmg {ohw_damage / 2, ohw_damage};
        return new Weapon(one_hand_weapon_names[rnd_name()], ohw_price, ohw_minimum_level, rnd_dmg(), 1);
    }

    static Weapon* generateTwoHandWeapon() {
        RandomInt rnd_dmg {thw_damage / 2, thw_damage};
        return new Weapon(two_hand_weapon_names[rnd_name()], thw_price, thw_minimum_level, rnd_dmg(), 2);
    }

    static Armor* generateArmor() {
        RandomInt rnd_dmr {a_damage_reduction / 2, a_damage_reduction};
        return new Armor(armor_names[rnd_name()], a_price, a_minimum_level, rnd_dmr());
    }

    static Potion* generatePotion() {
        RandomInt rnd_inc {pt_increment / 2, pt_increment};
        return new Potion(potion_names[rnd_name()], pt_price, pt_minimum_level, rnd_inc());
    }

    static IceSpell* generateIceSpell() {
        RandomInt rnd_rounds {1, max_rounds};
        return new IceSpell(ice_spell_names[rnd_name()], i_price, i_minimum_level, i_dmg_range, i_mana_required, i_dmg_reduction, rnd_rounds());
    }
    
    static FireSpell* generateFireSpell() {
        RandomInt rnd_rounds {1, max_rounds};
        return new FireSpell(fire_spell_names[rnd_name()], f_price, f_minimum_level, f_dmg_range, f_mana_required, f_defense_reduction, rnd_rounds());
    }

    static LightingSpell* generateLightingSpell() {
        RandomInt rnd_rounds {1, max_rounds};
        return new LightingSpell(lighting_spell_names[rnd_name()], l_price, l_minimum_level, l_dmg_range, l_mana_required, l_dodge_reduction, rnd_rounds());
    }
    ////////////////////////////////////////////////////////////////////////////
};