#include "World/Market.hpp"
#include "Game/Generator.hpp"
#include "Utilities/ColouredLogger.hpp"
#include "Utilities/Inputter.hpp"
#include "Utilities/Random.hpp"

void Market::createItemsToSell(int lower_bound, int upper_bound) {
    RandomInt rnd {lower_bound, upper_bound};
    no_items +=  rnd();

    rnd.change_bounds(0, 3);
    for (int i = 0; i < no_items; ++i) {
        if (rnd() == 0)       items_to_sell.push_back(Generator::generateOneHandWeapon());
        else if (rnd() == 1)  items_to_sell.push_back(Generator::generateTwoHandWeapon());
        else if (rnd() == 2)  items_to_sell.push_back(Generator::generateArmor());
        else                  items_to_sell.push_back(Generator::generatePotion());
    }
}

void Market::createSpellsToSell(int lower_bound, int upper_bound) {
    RandomInt rnd {lower_bound, upper_bound};
    no_spells +=  rnd();

    rnd.change_bounds(0, 2);
    for (int i = 0; i < no_spells; ++i) {
        if (rnd() == 0)       spells_to_sell.push_back(Generator::generateIceSpell());
        else if (rnd() == 1)  spells_to_sell.push_back(Generator::generateFireSpell());
        else                  spells_to_sell.push_back(Generator::generateLightingSpell());
    }
}

void Market::restockItems() {
    int diff = min_no_items - no_items;
    createItemsToSell(diff, min_no_items);
}

void Market::restockSpells() {
    int diff = min_no_spells - no_spells;
    createSpellsToSell(diff, min_no_spells);
}

Market::Market(int in_row, int in_column)
    : Square(in_row, in_column) 
{
    createItemsToSell(min_no_items, max_no_items);
    createSpellsToSell(min_no_spells, max_no_spells);
}

Market::~Market() {
    for (Item* i : items_to_sell)
        delete i;
    for (Spell* s : spells_to_sell)
        delete s;

    items_to_sell.clear();
    spells_to_sell.clear();
    heroes.clear();
}

void Market::adjustItemsAndSpells(int max_hero_level) {
    // We adjust the merchandise so that its attributes upgrade gradually
    // with the hero that has the highest level. We don't need to adjust
    // at early levels (1 - 2). 

    if (max_hero_level > 2) {
        for (Item* i : items_to_sell)
            i->adjust(max_hero_level);
        for (Spell* s : spells_to_sell)
            s->adjust(max_hero_level);
    }
}


bool Market::enter(const std::vector<Hero*>& heroes_to_enter) {
    int max_hero_level = 0;
    for (Hero* h : heroes_to_enter) {
        heroes.push_back(h);
        if (h->getLevel() > max_hero_level)
            max_hero_level = h->getLevel();
    }
    adjustItemsAndSpells(max_hero_level);
    access();
    return true;
}

void Market::exit() {
    Square::exit();
    if (no_items  < min_no_items)    restockItems();     //  We restock if we have less than min_no_items
    if (no_spells < min_no_spells)  restockSpells();     //  We restock if we have less than min_no_spells
}

void Market::access() {
    // Simple method to access the market's menu
    system("clear");
    int choice;
    do {
        ColouredLogger::LogMessageColoured("Market\n", ColouredLogger::Colour::MAGENTA);
        ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::MAGENTA);
        
        ColouredLogger::LogMessageColoured("Options:\n", ColouredLogger::Colour::WHITE); 
        std::cout << "1. Buying Menu\n";
        std::cout << "2. Selling Menu\n";
        std::cout << "3. Exit\n";

        choice = Inputter::GetInput("Choose base on index: ", 1, 3);
        ColouredLogger::ignoreLine();
        if (choice != 3) system("clear");
        
        if (choice == 1)        displayMenuToBuy();
        else if (choice == 2)   displayMenuToSell();
        
    } while (choice != 3);
}

void Market::displayMenuToBuy() {
    // Buying menu, we present the items and spells that are for sale 
    // and let the player decide if they want to buy something for each of
    // their heroes granted that certain requirements are met.

    int index = 1;
    for (Hero* hero : heroes) {
        ColouredLogger::LogMessageColoured("Buying menu\n", ColouredLogger::Colour::MAGENTA);
        ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::MAGENTA);
        std::cout << hero->getName() << " has " << hero->getMoney() << " amount of money\n";
        if (!hero->getMoney()) {
            ColouredLogger::PauseAndClearWithMessage("Press enter to return to Market's Menu...");
            return;
        }
        std::string answer = Inputter::GetInput("Do you wish to buy something (yes / no): ", "yes", "no");
        while (answer == "yes") {
            std::string category = Inputter::GetInput("Do you wish to buy an item or a spell (item / spell / exit): ", "item", "spell", "exit");
            if (category == "exit")
                break;
            else if (category == "item") {
                if (!no_items)
                    std::cout << "No items available for purchase...\n";
                else {
                    ColouredLogger::LogMessageColoured("Items for sale:\n", ColouredLogger::Colour::WHITE);
                    index = 1;
                    for (const Item* i : items_to_sell) {
                        std::cout << index << ". ";
                        i->printDetailed();
                        ++index;
                    }
                    int choice = Inputter::GetInput("Choose item based on index: ", 1, --index);
                    if (hero->buyItem(items_to_sell[choice - 1])) {
                        std::cout << "Item successfully bought!\n";
                        items_to_sell.erase(items_to_sell.begin() + choice - 1);
                        --no_items;
                    }
                    else 
                        std::cout << "Item purchase failed!\n";
                    ColouredLogger::ignoreLine();
                }
            }
            else {
                if (!no_spells)
                    std::cout << "No spells available for purchase...\n";
                else {
                    ColouredLogger::LogMessageColoured("Spells for sale:\n", ColouredLogger::Colour::WHITE);
                    index = 1;
                    for (const Spell* s : spells_to_sell) {
                        std::cout << index << ". ";
                        s->printDetailed();
                        ++index;    
                    }
                    int choice = Inputter::GetInput("Choose spell based on index: ", 1, --index);
                    if (hero->buySpell(spells_to_sell[choice - 1])) {
                        std::cout << "Spell successfully bought!\n";
                        spells_to_sell.erase(spells_to_sell.begin() + choice - 1);
                        --no_spells;
                    }
                    else 
                        std::cout << "Spell purchase failed!\n";
                    ColouredLogger::ignoreLine();
                }
            }
            answer = Inputter::GetInput("Do you wish to continue buying (yes / no): ", "yes", "no");
            system("clear");
            ColouredLogger::LogMessageColoured("Buying menu\n", ColouredLogger::Colour::MAGENTA);
            ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::MAGENTA);
        }
        system("clear");
    }
    system("clear");
}

void Market::displayMenuToSell() {
    // Selling menu, we let the player decide if they want to sell
    // some of the merchandise of each hero for half its starting price.
    
    for (Hero* hero : heroes) {
        ColouredLogger::LogMessageColoured("Selling menu\n", ColouredLogger::Colour::MAGENTA);
        ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::MAGENTA);
        if (!hero->getNoItems() && !hero->getNoSpells()) {
            std::cout << hero->getName() << " has neither items nor spells to sell...\n";
            ColouredLogger::PauseAndClearWithMessage("Press enter to return to Market's Menu...");
            continue;
        }
        std::cout << hero->getName() << " has " << hero->getMoney() << " amount of money\n";
        std::string answer = Inputter::GetInput("Do you wish to sell something for half its worth (yes / no): ", "yes", "no");
        while (answer == "yes") {
            std::string category = Inputter::GetInput("Do you wish to sell an item or a spell (item / spell / exit): ", "item", "spell", "exit");
            if (category == "exit")
                break;
            else if (category == "item") {
                if (!hero->getNoItems()) {
                    std::cout << "Hero has no items available for sale...\n";
                    break;
                }
                else {
                    while (true) {
                        std::string i_category = Inputter::GetInput("Do you wish to sell (weapon / armor / potion/ exit):", "weapon", "armor", "potion", "exit");
                        if (i_category == "exit")
                            break;
                        else if (i_category == "weapon") {
                            hero->printWeapons();
                            int no_weapons = hero->getNoWeapons();
                            if (no_weapons) {
                                int choice = Inputter::GetInput("Choose weapon to sell based on index: ", 1, no_weapons);
                                items_to_sell.push_back(hero->sellWeapon(choice - 1));
                                ColouredLogger::ignoreLine();
                                break;
                            }
                        }
                        else if (i_category == "armor") {
                            hero->printArmors();
                            int no_armors = hero->getNoArmors();
                            if (no_armors) {
                                int choice = Inputter::GetInput("Choose armor to sell based on index: ", 1, no_armors);
                                items_to_sell.push_back(hero->sellArmor(choice - 1));
                                ColouredLogger::ignoreLine();
                                break;
                            }
                        }
                        else {
                            hero->printPotions();
                            int no_potions = hero->getNoPotions();
                            if (no_potions) {
                                int choice = Inputter::GetInput("Choose potion to sell based on index: ", 1, no_potions);
                                items_to_sell.push_back(hero->sellPotion(choice - 1));
                                ColouredLogger::ignoreLine();
                                break;
                            }
                        }
                    }
                }
            }
            else {
                hero->printSpells();
                if (hero->getNoSpells()) {
                    int choice = Inputter::GetInput("Choose spell based on index: ", 1, hero->getNoSpells());
                    spells_to_sell.push_back(hero->sellSpell(choice - 1));
                    ColouredLogger::ignoreLine();
                }
            }
            answer = Inputter::GetInput("Do you wish to continue selling (yes / no): ", "yes", "no");
            if (answer == "no") return;
            system("clear");
            ColouredLogger::LogMessageColoured("Selling menu\n", ColouredLogger::Colour::MAGENTA);
            ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::MAGENTA);
        }
        system("clear");
    }
    system("clear");
}

void Market::printColoured() const {
    ColouredLogger::LogMessageColoured("$", ColouredLogger::MAGENTA);
}