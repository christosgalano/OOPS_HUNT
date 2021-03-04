#include "World/World.hpp"
#include "World/Market.hpp"
#include "World/Common.hpp"
#include "Game/Generator.hpp"
#include "Utilities/Inputter.hpp"
#include "Utilities/ColouredLogger.hpp"

void World::createWorld() { // The grid has a specific design
    // Row 0
    grid[0][0] = new Plain(0, 0);       

    grid[0][1] = new NonAccessible(0, 1);  

    grid[0][2] = new Camp(0, 2);   

    grid[0][3] = new Plain(0, 3);       

    grid[0][4] = new NonAccessible(0, 4);   

    grid[0][5] = new Common(0, 5, no_heroes, Common::Difficulty::MODERATE);   

    grid[0][6] = new Camp(0, 6);   

    grid[0][7] = new NonAccessible(0, 7);   

    grid[0][8] = new NonAccessible(0, 8);       

    grid[0][9] = new Common(0, 9, no_heroes, Common::Difficulty::HARD); 

    // Row 1
    grid[1][0] = new NonAccessible(1, 0);       

    grid[1][1] = new Common(1, 1, no_heroes, Common::Difficulty::EASY);

    grid[1][2] = new Plain(1, 2);       
    
    grid[1][3] = new Camp(1, 3); 

    grid[1][4] = new Plain(1, 4);       

    grid[1][5] = new Plain(1, 5);       

    grid[1][6] = new Plain(1, 6);       

    grid[1][7] = new NonAccessible(1, 7);       

    grid[1][8] = new Market(1, 8);  

    grid[1][9] = new NonAccessible(1, 9);  

    // Row 2
    grid[2][0] = new NonAccessible(2, 0);       

    grid[2][1] = new Plain(2, 1);  

    grid[2][2] = new Plain(2, 2);       
    
    grid[2][3] = new NonAccessible(2, 3);       
    
    grid[2][4] = new NonAccessible(2, 4);  
    
    grid[2][5] = new Plain(2, 5);       
    
    grid[2][6] = new Common(2, 6, no_heroes, Common::Difficulty::EASY);      
    
    grid[2][7] = new Plain(2, 7);       
    
    grid[2][8] = new Common(2, 8, no_heroes, Common::Difficulty::MODERATE); 

    grid[2][9] = new Plain(2, 9);       
    
    /// Row 3
    grid[3][0] = new Plain(3, 0);
    
    grid[3][1] = new NonAccessible(3, 1);
    
    grid[3][2] = new Common(3, 2, no_heroes, Common::Difficulty::MODERATE);

    grid[3][3] = new Market(3, 3);

    grid[3][4] = new Plain(3, 4);
    
    grid[3][5] = new NonAccessible(3, 5);

    grid[3][6] = new Plain(3, 6);

    grid[3][7] = new Camp(3, 7);

    grid[3][8] = new Market(3, 8);

    grid[3][9] = new NonAccessible(3, 9);

    // Row 4
    grid[4][0] = new NonAccessible(4, 0);

    grid[4][1] = new Plain(4, 1);
    
    grid[4][2] = new NonAccessible(4, 2);
    
    grid[4][3] = new Plain(4, 3);
    
    grid[4][4] = new Plain(4, 4);

    grid[4][5] = new Common(4, 5, no_heroes, Common::Difficulty::EASY);
    
    grid[4][6] = new NonAccessible(4, 6);
    
    grid[4][7] = new Camp(4, 7);

    grid[4][8] = new Common(4, 8, no_heroes, Common::Difficulty::MODERATE);
    
    grid[4][9] = new NonAccessible(4, 9);

    // Row 5
    grid[5][0] = new Camp(5, 0);
    
    grid[5][1] = new Common(5, 1, no_heroes, Common::Difficulty::EASY);
    
    grid[5][2] = new Camp(5, 2);

    grid[5][3] = new Common(5, 3, no_heroes, Common::Difficulty::MODERATE);

    grid[5][4] = new Plain(5, 4);
    
    grid[5][5] = new Plain(5, 5);
    
    grid[5][6] = new Market(5, 6);

    grid[5][7] = new Plain(5, 7);
    
    grid[5][8] = new Plain(5, 8);

    grid[5][9] = new NonAccessible(5, 9);

    // Row 6
    grid[6][0] = new Plain(6, 0);

    grid[6][1] = new NonAccessible(6, 1);
    
    grid[6][2] = new Plain(6, 2);

    grid[6][3] = new NonAccessible(6, 3);

    grid[6][4] = new Plain(6, 4);
    
    grid[6][5] = new Camp(6, 5);
    
    grid[6][6] = new Plain(6, 6);

    grid[6][7] =  new Market(6, 7);

    grid[6][8] = new Common(6, 8, no_heroes, Common::Difficulty::MODERATE);

    grid[6][9] = new Camp(6, 9);

    // Row 7
    grid[7][0] = new NonAccessible(7, 0);
    
    grid[7][1] = new Plain(7, 1);
    
    grid[7][2] = new Market(7, 2);

    grid[7][3] = new Plain(7, 3);
    
    grid[7][4] = new NonAccessible(7, 4);
    
    grid[7][5] = new Plain(7, 5);
    
    grid[7][6] = new Common(7, 6, no_heroes, Common::Difficulty::HARD);

    grid[7][7] = new Camp(7, 7);

    grid[7][8] = new Plain(7, 8);
    
    grid[7][9] = new NonAccessible(7, 9);

    // Row 8
    grid[8][0] = new Common(8, 0, no_heroes, Common::Difficulty::MODERATE);

    grid[8][1] = new NonAccessible(8, 1);
    
    grid[8][2] = new Plain(8, 2);
    
    grid[8][3] = new NonAccessible(8, 3);
    
    grid[8][4] = new Common(8, 4, no_heroes, Common::Difficulty::MODERATE);
    
    grid[8][5] = new NonAccessible(8, 5);
    
    grid[8][6] = new Plain(8, 6);

    grid[8][7] = new Plain(8, 7);

    grid[8][8] = new Common(8, 8, no_heroes, Common::Difficulty::HARD);
    
    grid[8][9] = new NonAccessible(8, 9);

    // Row  9
    grid[9][0] = new NonAccessible(9, 0);

    grid[9][1] = new NonAccessible(9, 1);

    grid[9][2] =  new Common(9, 2, no_heroes, Common::Difficulty::HARD);

    grid[9][3] = new Plain(9, 3);
    
    grid[9][4] = new Camp(9, 4);

    grid[9][5] = new NonAccessible(9, 5);

    grid[9][6] = new Common(9, 6, no_heroes, Common::Difficulty::HARD);
    
    grid[9][7] = new NonAccessible(9, 7);
    
    grid[9][8] = new NonAccessible(9, 8);
    
    grid[9][9] = new Market(9, 9);

}

void World::createHeroes() {
    // Based on the player's choice we create a certain number of heroes
    ColouredLogger::LogMessageColoured("Luck or Intuition\n", ColouredLogger::Colour::RED);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::RED);

    std::string answer =  Inputter::GetInput("Choose between these letters (A / B / C): ", "A", "B", "C");
    if (answer == "A") {
        std::cout << "Wise choice, ";    
        no_heroes = 2;
    }
    else if (answer == "B") {
        std::cout << "Excellent choice, ";
        no_heroes = 3;
    }
    else {
        std::cout << "Better luck next time, ";
        no_heroes = 1;
    }
    if (no_heroes > 1)
        std::cout << "you have been awarded " << no_heroes << " heroes!\n" << std::endl;
    else 
        std::cout << "you have been awarded " << no_heroes << " hero.\n" << std::endl;

    RandomInt rnd {0, 2};
    for (int i = 0; i < no_heroes; ++i) {
        if (rnd() == 0)       heroes.push_back(Generator::generateWarrior());
        else if (rnd() == 1)  heroes.push_back(Generator::generateSorcerer());
        else                  heroes.push_back(Generator::generatePaladin());
    }
}

World::~World() {
    for (int i = 0; i < rows; ++i) 
        for (int j = 0; j < columns; ++j)
            delete grid[i][j];

    for (Hero* h : heroes)
        delete h;
}

void World::initialize() {
    createHeroes();
    createWorld();
    ColouredLogger::PauseAndClear();
}

void World::move() {
    displayMap();   // We display the map so that the player can see where they want to move

    // Movement similar to a king's pawn (chess)
    int i = heroes_position.getX();
    int j = heroes_position.getY();

    if (i - 1 >= 0 && j - 1 >= 0)           moves.push_back(Point{i-1, j-1});

    if (i - 1 >= 0)                         moves.push_back(Point{i-1, j});
    
    if (i - 1 >= 0 && j + 1 < columns)      moves.push_back(Point{i-1, j+1});
    
    if (j - 1 >= 0)                         moves.push_back(Point{i, j-1});

    if (j + 1 < columns)                    moves.push_back(Point{i, j+1});

    if (i + 1 < rows && j - 1 >= 0)         moves.push_back(Point{i+1, j-1});

    if (i + 1 < rows)                       moves.push_back(Point{i+1, j});

    if (i + 1 < rows && j + 1 < columns)    moves.push_back(Point{i+1, j+1});

    ColouredLogger::ignoreLine();
    std::cout << "\nPossible moves when on square " << heroes_position << ":\n";
    int index = 1;
    for (const Point& p : moves)
        std::cout << index++ << ". " << p << '\n';

    std::cout << '\n';
    getCurrentSquare()->exit();
    heroes_last_position = heroes_position; // Update the position the player was before they moved

    --index;
    do {  // Choose a Square to move until the heroes enter it successfully
        int choice = Inputter::GetInput("Give position to move based on index: ", 1, index);
        ColouredLogger::ignoreLine();
        heroes_position = moves[choice - 1];
    } while (!getCurrentSquare()->enter(heroes));

    // If it is a common square and a battle occured and heroes lost, then the
    // heroes spawn at their last know position prior to entering this square.
    Common* c = dynamic_cast<Common*>(getCurrentSquare());
    if (c && c->getBattleOccured() && !c->getHeroesWon())
            heroes_position = heroes_last_position;
    moves.clear();
}

void World::displayMap() const {
    ColouredLogger::LogMessageColoured("MAP\n", ColouredLogger::Colour::CYAN);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::CYAN);

    int x = heroes_position.getX();
    int y = heroes_position.getY();

    std::cout << "  ";
    for (int j = 0; j < columns; ++j)
        std::cout << " " << j << " ";

    std::cout << '\n';

    for (int i = 0; i < rows; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < columns; ++j) {
            std::cout << " ";
            
            if (x == i && y == j)
                ColouredLogger::LogMessageColoured("*", ColouredLogger::WHITE);
            else 
                grid[i][j]->printColoured();
            
            std::cout << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n' << std::flush;
}

void World::checkInventory() {
    ColouredLogger::ignoreLine();
    for (int i = 0; i < no_heroes; ++i) {
        heroes[i]->checkInventory();
        std::cout << '\n';
        if (i == no_heroes - 1)
            ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");
        else 
            ColouredLogger::PauseAndClear();
    }
}

void World::showStatistics() const {
    ColouredLogger::ignoreLine();
    for (int i = 0; i < no_heroes; ++i) {
        ColouredLogger::LogMessageColoured("Statistics\n", ColouredLogger::Colour::BLUE);
        ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::BLUE);
        heroes[i]->printDetailed();
        std::cout << '\n';
        if (i == no_heroes - 1)
            ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");
        else 
            ColouredLogger::PauseAndClear();
    }
}

void World::showMapInfo() const {
    ColouredLogger::LogMessageColoured("Map Info\n", ColouredLogger::Colour::CYAN);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::CYAN);
    
    ColouredLogger::LogMessageColoured("Symbols and their meanings:\n", ColouredLogger::WHITE);

    ColouredLogger::LogMessageColoured("*", ColouredLogger::WHITE);
    std::cout << " -> Heroes Location\n";

    ColouredLogger::LogMessageColoured("~", ColouredLogger::YELLOW);
    std::cout << " -> Plain Square\n";

    ColouredLogger::LogMessageColoured("#", ColouredLogger::BLACK);
    std::cout << " -> NonAccessible Square\n";

    ColouredLogger::LogMessageColoured("^", ColouredLogger::GREEN);
    std::cout << " -> Camp Square\n";

    ColouredLogger::LogMessageColoured("$", ColouredLogger::MAGENTA);
    std::cout << " -> Market Square\n";   

    ColouredLogger::LogMessageColoured("C", ColouredLogger::RED);
    std::cout << " -> Common Square\n" << std::endl;

    ColouredLogger::ignoreLine();
    ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");
}