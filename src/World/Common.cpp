#include "World/Common.hpp"
#include "Entities/MonsterTypes.hpp"
#include "Game/Generator.hpp"
#include "Utilities/Inputter.hpp"
#include "Utilities/ColouredLogger.hpp"
#include "Utilities/Random.hpp"
#include <algorithm>

void Common::createMonsters() {
    // We set the upper and lower bound of no_monsters based on
    // the no_heroes the player controls and the difficulty.
    // Specifically:
    // 1 hero will face   : EASY {1}, MODERATE {1 to 2}, HARD{2} monsters
    // 2 heroes will face : EASY {1 to 2}, MODERATE {1 to 3}, HARD {2 to 3} monsters
    // 3 heroes will face : EASY {2}, MODERATE {2 to 4}, HARD {3 to 4} monsters

    if (no_heroes == 1) {
        min_no_monsters = 1;
        max_no_monsters = 2;
        if (difficulty == Common::Difficulty::EASY)
            max_no_monsters = 1;
        else if (difficulty == Common::Difficulty::HARD)
            min_no_monsters = 2;
    }
    else if (no_heroes == 2) {
        min_no_monsters = 1;
        max_no_monsters = 3;
        if (difficulty == Common::Difficulty::EASY) 
            max_no_monsters = 2;
        else if (difficulty == Common::Difficulty::HARD)
            min_no_monsters = 2;
    }
    else {
        min_no_monsters = 2;
        max_no_monsters = 4;
        if (difficulty == Common::Difficulty::EASY)
            max_no_monsters = 2;
        else if (difficulty == Common::Difficulty::HARD)
            min_no_monsters = 3;
    }
    
    RandomInt rnd {min_no_monsters, max_no_monsters};
    no_monsters = rnd();

    rnd.change_bounds(0, 2);    
    for (int i = 0; i < no_monsters; i++) {
        if (rnd() == 0)       alive_monsters.push_back(Generator::generateDragon());
        else if (rnd() == 1)  alive_monsters.push_back(Generator::generateExoskeleton());
        else                  alive_monsters.push_back(Generator::generateSpirit());
    }
}

Common::Common(int in_row, int in_column, int in_no_heroes, Difficulty in_difficulty) 
    : Square(in_row, in_column), no_heroes(in_no_heroes), difficulty(in_difficulty) 
{
    createMonsters();
}

Common::~Common() {
    for (Monster* m : alive_monsters)
        delete m;
    for (Monster* m : dead_monsters)
        delete m;

    alive_monsters.clear();
    dead_monsters.clear();
    heroes.clear();
}

void Common::adjustMonsters(int max_hero_level) {
    // The level of each monster will depend on max_hero_level & difficulty.
    // We distinguish 3 cases based on difficulty:
    // - EASY     : monster's level will be 1, 2 or 3 less than max_hero_level
    // - MODERATE : monster's level will be the same, 1 more or 1 less than max_hero_level
    // - HARD     : monster's level will be 1, 2 or 3 more than max_hero_level

    int new_level = max_hero_level;
    RandomInt r1 {1, 3}, r2 {-1, 1};
    if (difficulty == Common::Difficulty::EASY)
        new_level -= r1();
    else if (difficulty == Common::Difficulty::MODERATE)
        new_level += r2();  
    else 
        new_level += r1();

    // Adjust all the monsters according to new_level
    std::for_each(alive_monsters.begin(), alive_monsters.end(), [=](Monster* m) { m->adjust(new_level); } );
}

bool Common::enter(const std::vector<Hero*>& heroes_to_enter) {
    battle_occured = false;
    system("clear");
    ColouredLogger::LogMessageColoured("Common\n", ColouredLogger::Colour::RED);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::RED);
    std::cout << "You have entered a common square. A battle may occur.\n";
    ColouredLogger::PauseWithMessage("Press enter to find out...");

    int max_hero_level = 0;
    for (Hero* h : heroes_to_enter) {
        heroes.push_back(h);
        if (h->getLevel() > max_hero_level)
            max_hero_level = h->getLevel();
    }
    
    RandomInt rnd_c {1, 100};
    if (chance_to_battle > rnd_c()) {
        system("clear");
        battle_occured = true;
        heroes_won = false;
        adjustMonsters(max_hero_level);
        battle();
    }
    else 
        std::cout << "\nYou got lucky, no battle this time\n";
    ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");
    return true;
}

void Common::access() {
    system("clear");
    ColouredLogger::LogMessageColoured("Common\n", ColouredLogger::Colour::RED);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::RED);    
    std::cout << "You are currently occupying a common square\n";
    if (battle_occured)  // If a battle occured then the player won, otherwise they would have spawned at previous location.
        std::cout << "You won the battle that occured\n";
    else 
        std::cout << "You got lucky, no battle this time\n";
    ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");   
}

int Common::getAliveHeroes() {
    return std::count_if(heroes.begin(), heroes.end(), [](Hero* h) { return !h->getHasFainted(); } );
}

void Common::ckeckMonsters() {
    int no_monsters_alive = static_cast<int>(alive_monsters.size());
    if (!no_monsters_alive) return;

    // When a monster dies we erase it from the alive_monsters vector
    // and add it in the dead_monsters and died_this_round vectors. 
    for (int i = 0; i < no_monsters_alive; ++i) {
        if (alive_monsters[i]->getHasFainted()) {
            died_this_round.push_back(alive_monsters[i]);
            dead_monsters.push_back(alive_monsters[i]);
            alive_monsters.erase(alive_monsters.begin() + i);
        }
    }
}

void Common::updateRound(int round, std::vector<std::unordered_set<Monster*>>& vec) {
    system("clear");
    std::string temp = "End of round " + std::to_string(round) + '\n';
    ColouredLogger::LogMessageColoured(temp, ColouredLogger::Colour::RED);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::RED);
    
    // When a monster dies, all heroes get experience and money based on level and participation
    if (round % 2 != 0 && died_this_round.size()) {
        ColouredLogger::LogMessageColoured("Kill gains:\n", ColouredLogger::WHITE);
        for (Monster* m : died_this_round) {
            for (int i = 0; i < no_heroes; ++i)
                heroes[i]->killGains(m, searchMonster(vec[i], m));
        }

        died_this_round.clear();
        std::cout << '\n';
    }

    // If heroes won return - we know heroes are not dead because this function would not have been called
    if (!alive_monsters.size()) {
        ColouredLogger::LogMessageColoured("HEROES WON !!!\n\n", ColouredLogger::CYAN);
        return;
    }

    // Update alive heroes and monsters
    std::for_each(heroes.begin(), heroes.end(), [](Hero* h) { h->update(); } );
    std::for_each(alive_monsters.begin(), alive_monsters.end(), [](Monster* m) { m->update(); } );

    std::cout << '\n';
    ColouredLogger::PauseAndClearWithMessage("Press enter to begin the next round...");
}

bool Common::searchMonster(std::unordered_set<Monster*>& damaged_monsters, Monster* m) {
    // Returns true if the hero has damaged the specific monster
    for (Monster* monster : damaged_monsters)
        if (monster == m)
            return true;
    return false;
}


void Common::reviveBeings() {
    // Revive the dead monsters
    for (Monster* m : dead_monsters) {
        m->revive();
        alive_monsters.push_back(m);
    }
    dead_monsters.clear();

    // If not all heroes are dead it means they won
    if (getAliveHeroes())
        heroes_won = true;

    // Revive the dead heroes
    std::for_each(heroes.begin(), heroes.end(), [](Hero* h) { if(h->getHasFainted()) h->revive(); } );

}
void Common::battle() {
    ColouredLogger::LogMessageColoured("Battle\n", ColouredLogger::Colour::RED);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::RED);
    
    ColouredLogger::LogMessageColoured("Heroes:\n", ColouredLogger::WHITE);
    for (const Hero* h : heroes) 
        std::cout << "- " << h->getName() << '\n';

    std::cout << std::endl;
    ColouredLogger::LogMessageColoured("Monsters:\n", ColouredLogger::WHITE);
    for (const Monster* m : alive_monsters) 
        std::cout << "- " << m->getName() << '\n';

    std::cout << std::endl;
    ColouredLogger::PauseWithMessage("Press enter to begin...");

    int rounds = 1;
    
    // A monster attacks a random alive hero 
    RandomInt rnd_h {0, no_heroes - 1};
    
    // In order to keep up with which monsters has each hero damaged
    // we use a vector of unordered_sets of Monster*, which also ensures
    // that no monster will appear twice in a hero's unordered_set.
    std::vector<std::unordered_set<Monster*>> has_damaged(no_heroes);

    while (true) {
        if (rounds > 1) {   // Before we start each round we call the 2 update methods
            ckeckMonsters();
            if (!getAliveHeroes()) {
                system("clear");
                ColouredLogger::LogMessageColoured("MONSTERS WON !!!\n", ColouredLogger::RED);
                std::cout << "Heroes will spawn at the square they were prior to entering this one\nOnly half of their health will be restored\n";
                break;
            }
            updateRound(rounds - 1, has_damaged);
            if (!alive_monsters.size()) break;
        }
        else 
            system("clear");

        std::string temp = "Round " + std::to_string(rounds) + '\n';
        ColouredLogger::LogMessageColoured(temp, ColouredLogger::Colour::RED);
        ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::RED);

        if (rounds % 2 != 0) {  // Heroes rounds are odd numbers
            ColouredLogger::PauseWithMessage("Heroes turn, press enter to attack...");
            for (int i = 0; i < no_heroes; ++i) {
                system("clear");

                ckeckMonsters();   // Before each hero's action we update the monsters
                if (!alive_monsters.size()) break;
                
                if (!heroes[i]->getHasFainted())
                    heroes[i]->printBattle();
                else 
                    continue;

                while (true) {  // Each hero has 3 possible actions
                    ColouredLogger::LogMessageColoured("\nOptions:\n", ColouredLogger::WHITE);
                    std::cout << "1. Regular attack\n";
                    std::cout << "2. Cast spell\n";
                    std::cout << "3. Use potion\n";
                    int option = Inputter::GetInput("Choose based on index: ", 1, 3);
                    system("clear");
                    if (option == 3) {
                        if (heroes[i]->hasPotionInUse()) {
                            ColouredLogger::LogMessageColoured(heroes[i]->getName(), ColouredLogger::CYAN);
                            std::cout << " is already using a potion\n";
                            continue;
                        }

                        int no_potions = heroes[i]->getNoPotions();
                        if (!no_potions) {
                            ColouredLogger::LogMessageColoured(heroes[i]->getName(), ColouredLogger::CYAN);
                            std::cout << " has no potions available\n";
                            continue;
                        }
                        else
                            heroes[i]->printPotions();

                        int potion_choice = Inputter::GetInput("Choose potion based on index: ", 1, no_potions);
                        heroes[i]->use(potion_choice - 1);          
                        break;
                    }
                    else {

                        if (option == 2 && !heroes[i]->getNoSpells()) {
                            ColouredLogger::LogMessageColoured(heroes[i]->getName(), ColouredLogger::CYAN);
                            std::cout << " has no spells available\n";
                            continue;
                        }

                        int index = 1;
                        ColouredLogger::LogMessageColoured("Monsters:\n", ColouredLogger::RED);
                        for (Monster* m : alive_monsters) {
                            std::string temp = std::to_string(index) + ". ";
                            ColouredLogger::LogMessageColoured(temp, ColouredLogger::RED);
                            m->printBattle();
                            ++index;
                        } 

                        int monster_to_attack = Inputter::GetInput("Choose monster to attack based on index: ", 1, --index);
                        Monster* m = alive_monsters[monster_to_attack - 1];
                        if (option == 1) {
                            heroes[i]->attack(m);
                            has_damaged[i].insert(m);
                            ColouredLogger::ignoreLine();
                            ColouredLogger::Pause();
                            break;
                        }
                        else if (option == 2) {
                            int no_spells = heroes[i]->getNoSpells();
                            if (no_spells) {
                                heroes[i]->printSpells();
                                int spell_choice = Inputter::GetInput("Choose spell based on index: ", 1, no_spells);
                                if (heroes[i]->castSpell(m, spell_choice - 1)) {
                                    has_damaged[i].insert(m);
                                    ColouredLogger::ignoreLine();
                                    ColouredLogger::Pause();
                                    break;
                                }
                                else 
                                    continue;
                            }
                        }
                    }
                }
            }
        }
        else { // Monsters rounds are even numbers
            std::cout << "Monster's turn to attack:\n";
            for (Monster* m : alive_monsters) {   
                if (!getAliveHeroes())  break;
                
                Hero* h;
                do {  // Randomly attack an alive hero
                    h = heroes[rnd_h()];
                } while (h->getHasFainted());

                m->attack(h); 
            }
            std::cout << '\n'; 
            ColouredLogger::Pause();
        }
        ++rounds;
    }
    
    // Clear the unordered_sets regarding which hero damaged which monsters
    for (int i = 0; i < no_heroes; ++i)
        has_damaged[i].clear();
    has_damaged.clear();

    reviveBeings();
}

void Common::printColoured() const {
    ColouredLogger::LogMessageColoured("C", ColouredLogger::RED);
}