#pragma once
#include "World/Square.hpp"
#include <unordered_set>

class Monster; // Forward declaration

class Common : public Square {
public:
    enum class Difficulty{ EASY, MODERATE, HARD };
private:
    // Alive and dead monsters
    std::vector<Monster*> alive_monsters;
    std::vector<Monster*> dead_monsters;

    // Current no_beings 
    const int no_heroes;  // no_heroes the player controls
    int no_monsters {};

    // How difficult will the battle be for the player
    Difficulty difficulty;

    // Each common square can contain from min_no_monsters to max_no_monsters monsters
    int min_no_monsters;
    int max_no_monsters;     

    static constexpr double chance_to_battle {60.0};   // It means there is a 60% to battle

    // Stores the monster that died each round
    std::vector<Monster*> died_this_round;

    bool battle_occured;     // Tells if battle occured upon entering
    bool heroes_won;         // Tells if heroes won the last battle that occured - if they lost it means they all died

    // Creation methods
    void createMonsters();
    void adjustMonsters(int max_hero_level);

    // Battle methods
    void battle();
    void updateRound(int round, std::vector<std::unordered_set<Monster*>>& vec);
    void ckeckMonsters();
    bool searchMonster(std::unordered_set<Monster*>& damaged_monsters, Monster* m);
    void reviveBeings();
    int getAliveHeroes();
    
public:    
    // Constructor - Destructor
    Common(int in_row, int in_column, int in_no_heroes, Difficulty in_difficulty);
    ~Common();

    // Accessors
    bool getBattleOccured() const { return battle_occured; }
    bool getHeroesWon()     const { return heroes_won;     }

    // Methods
    bool enter(const std::vector<Hero*>& heroes_to_enter) override;
    void access() override;
    void printColoured() const override;
};