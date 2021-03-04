#pragma once
#include "World/Square.hpp"
#include "World/Point.hpp"

// We don't include Market.hpp - Common.hpp here because there is no need to.
// We include them in the .cpp file.

/// The World class represents the world where the game takes place ... It basically           ///
/// is a rows x columns matrix of Square* which the player can explore by moving their         ///
/// group of heroes one square each time ... The player's movement is defined exactly like the ///
/// king's pawn at chess - provided they don't try to enter a NonAccessible square ...         ///
/// The World's grid is specifically designed, meaning that the Squares are not randomly       ///
/// generated but precisely chosen in order to offer a fun and challenging experience ...      ///

class World {
private:
    // Grid's data
    static constexpr int rows {10};
    static constexpr int columns {10};
    Square* grid[rows][columns];

    // A player can control a group of min_no_heroes to max_no_heroes heroes
    static constexpr int min_no_heroes {1};
    static constexpr int max_no_heroes {3};

    // Heroes regarding data/methods
    int no_heroes;
    std::vector<Hero*> heroes;
    Point heroes_position;
    Point heroes_last_position;
    std::vector<Point> moves;   // Possible moves the player can make

    // Creation methods
    void createWorld();
    void createHeroes();

public:
    // Constructor - Destructor
    World() = default;
    ~World();

    // Accessor - Current square the heroes are on
    Square* getCurrentSquare() { return grid[heroes_position.getX()][heroes_position.getY()]; }

    // Methods
    void initialize();
    void move();
    void checkInventory();
    void displayMap()     const;
    void showStatistics() const;
    void showMapInfo()    const;
};