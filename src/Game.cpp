#include "Game.h"
#include "Spacecraft.h"
#include "Astro.h"
#include "Planet.h"
#include "Moon.h"
#include "FlightRecorder.h"
#include "Thruster.h"

#include <iostream>

Game::Game()
    : spacecraft(std::make_unique<Spacecraft>()), 
      astro(std::make_unique<Planet>()), 
      flightRecorder("flight_log.txt")
      {
        flightRecorder.record("Game initialized.");
        spacecraft->addComponent(std::make_unique<Thruster>());
      }

void Game::run() {};

