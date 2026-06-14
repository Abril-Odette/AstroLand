#include "Game.h"
#include "Planet.h"
#include "Moon.h"
#include "Thruster.h"
#include "AstrolandException.h"

#include <iostream>
#include <iomanip>

Game::Game()
    : spacecraft(std::make_unique<Spacecraft>(
      "AstroLander", Vector2D(0.0, 3500.0), 500.0, 800.0)), 
      astro(std::make_unique<Planet>(
        "Mars", 6.39e23, 3.389e6, Vector2D(0.0, 0.0), false, 0.0)), 
      flightRecorder("logs/flight.log")
      {
        flightRecorder.record("[GAME] initialized.");
        spacecraft->addComponent(std::make_unique<Thruster>(100.0, 50.0, 5000.0, 15000.0, 8.0, Vector2D(0.0, 1.0))
      );
      }

void Game::run() {
  try {
    std::cout << "===== AstroLand Simulator =====" << std::endl;
    std::cout << "Target body: " << astro->getName() << std::endl;
    std::cout << "Surface gravity: " << std::fixed << std::setprecision(2) << astro->surfaceGravity() << " m/s²" << std::endl;

    flightRecorder.record("[GAME] Game started.");

    const double dt = 0.1; 
    const int maxSteps = 2000;

    for (int step = 0; step < maxSteps; ++step){
      spacecraft->update(*astro, dt);

      if (step % 50 == 0) {
        std::cout << "t = " <<std::setw(5) << step 
        << "s | Position: " << spacecraft->getPosition()
        << " | Velocity: " << spacecraft->getVelocity()
        << " | Fuel: " << std::setprecision(1) << spacecraft->getFuel()
        << std::endl;

        flightRecorder.record("[GAME] Time: " + std::to_string(step) + 
        "s,  Y Position: " + std::to_string(spacecraft->getPosition().y) + 
        ", Velocity: " + std::to_string(spacecraft->getVelocity().x) + 
        ", Fuel: " + std::to_string(spacecraft->getFuel()));
      }

      if (spacecraft->checkLanding(*astro)) {
        std::cout << "Landing at t = " << step << "s" << std::endl;
        flightRecorder.record("[GAME] Landing event at time: " + std::to_string(step));
        break;
      }
    }

    flightRecorder.saveLogsToFile();
    std::cout << "Game ended. Flight log saved." << std::endl;

  } catch (const AstrolandException& ex) {
    std::cerr << "[AstroLandException]: " << ex.what() << std::endl;
    flightRecorder.record(std::string("[ERROR] ") + ex.what());
  } catch (const std::exception& ex) {
    std::cerr << "[std::exception]: " << ex.what() << std::endl;
    flightRecorder.record(std::string("[ERROR] Unexpected: ") + ex.what());
  }
};