#pragma once
#include "Entities/HeroTypes.hpp"

/// Abstract class that represents a square of the grid ///

class Square {
protected:  
    int row;
    int column;
    std::vector<Hero*> heroes;  // Heroes occupying the square
public:
    // Constructor - Destructor
    Square(int in_row, int in_column)
        : row(in_row), column(in_column) {}
    virtual ~Square() {}

    // Methods
    virtual bool enter(const std::vector<Hero*>& heroes_to_enter) = 0;
    virtual void exit() { heroes.clear(); }
    virtual void access() = 0;
    virtual void printColoured() const = 0;
};


/// Child classes:                                                                      ///
/// - NonAccessible :  cannot be occupied by any hero                                   ///
/// - Plain         :  heroes can enter this square but nothing special happens on it   ///
/// - Camp          :  upon entering this square the player can rest their heroes       ///
/// - Common        :  there is a 60% chance that a battle will occur on this square    ///
/// - Market        :  the player can buy and sell merchandise on this square           ///

class NonAccessible : public Square {   
public:
    // Constructor
    NonAccessible(int in_row, int in_column)
        : Square(in_row, in_column) {}

    // Methods
    bool enter(const std::vector<Hero*>& heroes_to_enter) override;
    void access() override {} // Does nothing, will never be used because the player cannot enter this type of Square
    void printColoured() const override;
};


class Plain : public Square {
public:
    // Constructor
    Plain(int in_row, int in_column)
        : Square(in_row, in_column) {}
    
    // Methods
    bool enter(const std::vector<Hero*>& heroes_to_enter) override;
    void access() override;
    void printColoured() const override;
};


class Camp : public Square {
public:
    // Constructor
    Camp(int in_row, int in_column)
        : Square(in_row, in_column) {}
    
    // Methods
    bool enter(const std::vector<Hero*>& heroes_to_enter) override;
    void access() override;
    void printColoured() const override;
};