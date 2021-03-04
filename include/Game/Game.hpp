#include "World/World.hpp"
#include "Utilities/ColouredLogger.hpp"

/// Game is a sinleton class and its main purpose is to provide a more pleasant interface for the user ... ///
/// The game's main functionality - besides the Main Menu - is implemented in the World class ...          ///

class Game {    // Singleton class
private:
    World world;
    bool quit_game {false};

    Game();  // Private constructor

    void startGame();   // Called upon creation

    void startingScreen() const;
    
    void displayMenu();  // Display Main Menu
    
    // Methods regarding Main Menu's options
    void move()             { world.move();           }
    void checkInventory()   { world.checkInventory(); }
    void access()           { world.getCurrentSquare()->access(); }
    
    void showStatistics()   const { world.showStatistics(); }
    void showMapInfo()      const { world.showMapInfo();    }
    
    void displayMap() const;   

public:
    // This is the static method that controls the access to the singleton
    // instance. On the first run, it creates a singleton object and places it
    // into the static field. On subsequent runs, it returns the user the existing
    // object stored in the static field.    
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
   
    // Singletons should not be cloneable or assignable
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;
	
    // Methods
    bool exit() const { return quit_game; }
    void update();
};