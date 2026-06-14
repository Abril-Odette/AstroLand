#include "Game.h"
#include "Spacecraft.h"
#include "Astro.h"
#include "Planet.h"
#include "Moon.h"
#include "FlightRecorder.h"
#include "Thruster.h"

#include <iostream>
#include <iomanip>

Game::Game()
    : spacecraft(std::make_unique<Spacecraft>()), 
      astro(std::make_unique<Planet>()), 
      flightRecorder("flight_log.txt")
      {
        flightRecorder.record("Game initialized.");
        spacecraft->addComponent(std::make_unique<Thruster>());
      }

void Game::run() {
  std::cout << "===== AstroLand Simulator =====" << std::endl;
  std::cout << "Target body: " << astro->getName() << std::endl;
  std::cout << "Surface gravity: " << std::fixed << std::setprecision(2) << astro->surfaceGravity() << " m/s²" << std::endl;

  flightRecorder.record("[GAME] Game started.");

  double dt = 0.1; 
  int maxSteps = 2000;

  for (int step = 0; step < maxSteps; ++step){
    spacecraft->update(*astro, dt);

    if (step %100 == 0) {
      std::cout << "t = " <<std::setw(5) << step 
      << "s | Position: " << spacecraft->getPosition()
      << " | Velocity: " << spacecraft->getVelocity()
      << " | Fuel: " << std::setprecision(1) << spacecraft->getFuel()
      << std::endl;

      flightRecorder.record("[GAME] Time: " + std::to_string(step) + "s, Position: " + std::to_string(spacecraft->getPosition().y) + "," + std::to_string(spacecraft->getPosition().y) + ", Velocity: " + std::to_string(spacecraft->getVelocity().x) + "," + std::to_string(spacecraft->getVelocity().y) + ", Fuel: " + std::to_string(spacecraft->getFuel()));
    }

    if (spacecraft->checkLanding(*astro)) {
      std::cout << "Landing at t = " << step << std::endl;
      flightRecorder.record("[GAME] Landing event at time: " + std::to_string(step));
      break;
    }
  }

  flightRecorder.saveLogsToFile();
  std::cout << "Game ended. Flight log saved." << std::endl;
};

