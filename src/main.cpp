#include "Game.h"
#include "AstrolandException.h"
#include <iostream>

int main() {
    try {
        Game game;
        game.run();
    } catch (const AstrolandException& ex) {
        std::cerr << "[AstroLandException]: " << ex.what() << std::endl;
        return 1;
    } catch (const std::exception& ex) {
        std::cerr << "[Fatal]: " << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}