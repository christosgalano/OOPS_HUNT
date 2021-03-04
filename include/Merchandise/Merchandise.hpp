#pragma once
#include <string>

class Merchandise {
protected:
    std::string name;
    int price;
    int minimum_level; // Minimum_level for the player to be in order to be able to buy this

    // Used to scale merchandise's price
    const int initial_price;

    void adjustPrice(int level);
    void adjustMinimumLevel(int level);

public:
    // Constructor - Destructor
    Merchandise(const std::string& in_name, int in_price, int in_minimum_level);
    virtual ~Merchandise() {}

    // Accessors
    std::string getName() const { return name;          }
    int getPrice()        const { return price;         }
    int getMinimumLevel() const { return minimum_level; }

    // Methods 
    virtual void adjust(int level);
    virtual void printPlain()      const = 0;
    virtual void printDetailed()   const = 0;
    virtual void printStatistics() const = 0;   
};