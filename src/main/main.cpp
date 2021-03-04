#include "Game/Game.hpp"

int main() {
    Game& game = Game::getInstance();
    
    while(!game.exit())  // Game loop
        game.update();
}