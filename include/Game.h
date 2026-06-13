#ifndef GAME_H
#define GAME_H

#include <memory>

#include"Spacecraft.h"
#include"FlightRecorder.h"
#include"Astro.h"

class Game {
    private:
        std::unique_ptr<Spacecraft> spacecraft;
        std::unique_ptr<Astro> astro;
        FlightRecorder flightRecorder;

    public:
    Game();
    void run();
    
};

#endif