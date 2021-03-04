#include "Game/Game.hpp"
#include "Utilities/Inputter.hpp"

Game::Game()  { startGame(); }

void Game::startingScreen() const {
    system("clear");
    std::string message = "OOP'S HUNT";
    ColouredLogger::LogMessageColoured("+------------------------------------------------------------------+\n", ColouredLogger::MAGENTA);
    ColouredLogger::LogMessageColoured("|                                                                  |\n", ColouredLogger::MAGENTA);  
    ColouredLogger::LogMessageColoured("|                                                                  |\n", ColouredLogger::MAGENTA);  
    ColouredLogger::LogMessageColoured("|", ColouredLogger::MAGENTA);
    bool front = true;
    for (int i = message.length(); i < 66; ++i) {
        if (front)
            message = " " + message;
        else
            message = message + " ";
        front = !front;
    }

    ColouredLogger::LogMessageColoured(message, ColouredLogger::MAGENTA);

    ColouredLogger::LogMessageColoured("|\n", ColouredLogger::MAGENTA);  
    ColouredLogger::LogMessageColoured("|                                                                  |\n", ColouredLogger::MAGENTA); 
    ColouredLogger::LogMessageColoured("|                                                                  |\n", ColouredLogger::MAGENTA); 
    ColouredLogger::LogMessageColoured("+------------------------------------------------------------------+\n\n", ColouredLogger::MAGENTA);

    ColouredLogger::PauseAndClearWithMessage("\n                         Press enter to play");
}

void Game::startGame() {
    startingScreen();
    world.initialize();
}

void Game::displayMenu() {
    ColouredLogger::LogMessageColoured("MAIN MENU\n", ColouredLogger::Colour::MAGENTA);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::MAGENTA);

    ColouredLogger::LogMessageColoured("Options:\n", ColouredLogger::WHITE);
    std::cout << "1. Move\n";
    std::cout << "2. Display Map\n";
    std::cout << "3. Check Inventory\n";
    std::cout << "4. Show Statistics\n";
    std::cout << "5. Map Info\n";
    std::cout << "6. Access Square\n";
    std::cout << "7. Quit Game\n";

    int choice = Inputter::GetInput("Choose based on index: ", 1, 7);
    if (choice == 7) {
        ColouredLogger::ignoreLine();
        std::string answer = Inputter::GetInput("Are you sure you want to quit (yes / no): ", "yes", "no");
        if (answer == "yes") quit_game = true;
        return;
    }

    system("clear");

    switch (choice) {
        case 1: move();            break;
        case 2: displayMap();      break;
        case 3: checkInventory();  break;
        case 4: showStatistics();  break;
        case 5: showMapInfo();     break;
        case 6: ColouredLogger::ignoreLine(); access(); break;
    }

}

void Game::displayMap() const {
    world.displayMap(); 
    ColouredLogger::ignoreLine();
    ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");
}

void Game::update() {
    system("clear");
    displayMenu();
    system("clear");
}