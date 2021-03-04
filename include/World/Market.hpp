#pragma once
#include "World/Square.hpp"

class Market : public Square {
private:
    // Merchandise for sale
    std::vector<Item*> items_to_sell;
    std::vector<Spell*> spells_to_sell;

    // Current no_merchandise
    int no_items  {};
    int no_spells {};

    // Each market can sell from min_no_items to max_no_items items
    static constexpr int min_no_items   {5};
    static constexpr int max_no_items  {12};     
    
    // Each market can sell from min_no_spells to max_no_items spells
    static constexpr int min_no_spells  {3};
    static constexpr int max_no_spells {10};

    // Methods regarding the creation and adjustment of the merchandise
    void createItemsToSell(int lower_bound, int upper_bound);
    void createSpellsToSell(int lower_bound, int upper_bound);
    void restockItems();
    void restockSpells();
    void adjustItemsAndSpells(int max_hero_level);
    
public:
    // Constructor - Destructor
    Market(int in_row, int in_column);
    ~Market();
    
    // Methods
    bool enter(const std::vector<Hero*>& heroes_to_enter) override;
    void exit() override;
    void access() override;
    void displayMenuToBuy();
    void displayMenuToSell();
    void printColoured() const override;
};