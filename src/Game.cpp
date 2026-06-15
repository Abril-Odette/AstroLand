#include "Game.h"
#include "Planet.h"
#include "Moon.h"
#include "Thruster.h"
#include "AstrolandException.h"
#include "FuelSensor.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

static void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

static void printAltitudeBar(double altitude, double maxAlt) {
  const int BAR_HEIGHT = 15;
  int level = 0;
  if (maxAlt > 0)
  level = static_cast<int>((altitude / maxAlt) * BAR_HEIGHT);
  if (level > BAR_HEIGHT) level = BAR_HEIGHT;
  if (level < 0) level = 0;

  std::cout << "  Altura\n";
    for (int i = BAR_HEIGHT; i >= 0; --i) {
        if (i == level)
            std::cout << "  |  [^]\n";   // spaceship
        else if (i == 0)
            std::cout << "  |====|\n";   // ground
        else
            std::cout << "  |    |\n";
    }
}

static void printFuelBar(double fuel, double maxFuel) {
    const int WIDTH = 20;
    int filled = (maxFuel > 0) ? static_cast<int>((fuel / maxFuel) * WIDTH) : 0;
    std::cout << "  Fuel [";
    for (int i = 0; i < WIDTH; ++i)
        std::cout << (i < filled ? '#' : '.');
    std::cout << "] " << std::fixed << std::setprecision(1) << fuel << " kg\n";
}

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

      spacecraft->addComponent(
        std::make_unique<FuelSensor>(100.0, 5.0, 500.0, 800.0)
      );
      }

void Game::run() {
  try {
    clearScreen();
        std::cout << "\n";
        std::cout << "  +========================================+\n";
        std::cout << "  |         A S T R O L A N D             |\n";
        std::cout << "  |   Space Landing Simulator              |\n";
        std::cout << "  +========================================+\n\n";
        std::cout << "  Celestial body : " << astro->getName() << "\n";
        std::cout << "  Surface gravity: " << std::fixed << std::setprecision(2)
                  << astro->surfaceGravity() << " m/s^2\n\n";

        std::cout << "  Controls:\n";
        std::cout << "  [t] + Enter  ->  Fire thruster\n";
        std::cout << "  [s] + Enter  ->  Cut thruster\n";
        std::cout << "  [q] + Enter  ->  Abort mission\n";
        std::cout << "  [Enter]      ->  Advance 1 second\n\n";
        std::cout << "  Press Enter to begin...";
        std::cin.ignore();

        flightRecorder.record("[GAME] Game started.");

    const double dt = 0.05; 
    const double STEP_SECS  = 1.0;
    const int    PHYS_STEPS = static_cast<int>(STEP_SECS / dt);
    const double MAX_ALT    = 3500.0;
    const double INIT_FUEL  = 800.0;

    double elapsedTime = 0.0;

    while (true) {
            // --- telemetry ---------------------------------------------------
            double surfaceY = astro->getPosition().y + astro->getRadius();
            double altitude = spacecraft->getPosition().y - surfaceY;
            double speed    = spacecraft->getVelocity().magnitude();
            double vy       = spacecraft->getVelocity().y;
            double fuel     = spacecraft->getFuel();
            bool   burning  = spacecraft->isThrusterActive();

          clearScreen();
            std::cout << "\n";
            std::cout << "  ============== TELEMETRY ===============\n";
            std::cout << "  Time       : " << std::fixed << std::setprecision(1)
                      << elapsedTime << " s\n";
            std::cout << "  Altitude   : " << std::setprecision(1) << altitude << " m\n";
            std::cout << "  Speed      : " << std::setprecision(2) << speed    << " m/s\n";
            std::cout << "  Vert. vel. : " << std::setprecision(2) << vy       << " m/s"
                      << (vy < 0 ? "  [descending]" : "  [ascending]") << "\n";
            std::cout << "  Thruster   : " << (burning ? "[ON]  FIRING" : "[OFF] idle") << "\n";
            printFuelBar(fuel, INIT_FUEL);

            if (altitude < 200.0 && speed > 5.0)
                std::cout << "\n  *** WARNING: DANGEROUS SPEED - BRAKE NOW ***\n";
            else if (altitude < 500.0)
                std::cout << "\n  Approaching surface...\n";
            else
                std::cout << "\n";

            std::cout << "\n";
            printAltitudeBar(altitude, MAX_ALT);
            std::cout << "\n";
            std::cout << "  ========================================\n";
            std::cout << "  Command> ";

            std::string line;
            std::getline(std::cin, line);
            char cmd = line.empty() ? ' ' : line[0];

            if (cmd == 'q') {
                std::cout << "\n  Mission aborted by pilot.\n";
                flightRecorder.record("[GAME] Mission aborted by user.");
                break;
            }
            if (cmd == 't') {
                spacecraft->setThrusterActive(true);
                flightRecorder.record("[GAME] Thruster ON at t=" + std::to_string(elapsedTime));
            }
            if (cmd == 's') {
                spacecraft->setThrusterActive(false);
                flightRecorder.record("[GAME] Thruster OFF at t=" + std::to_string(elapsedTime));
            }

            bool finished = false;
            for (int i = 0; i < PHYS_STEPS && !finished; ++i) {
                spacecraft->update(*astro, dt);
                elapsedTime += dt;

                if (spacecraft->checkLanding(*astro))
                    finished = true;
            }

            std::ostringstream oss;
            oss << "[STEP] t=" << std::fixed << std::setprecision(1) << elapsedTime
                << " alt=" << std::setprecision(0) << altitude
                << " spd=" << std::setprecision(2) << speed
                << " fuel=" << std::setprecision(1) << fuel
                << (burning ? " BURN" : "");
            flightRecorder.record(oss.str());

            if (finished) {
                clearScreen();
                double impactSpeed = speed;
                if (spacecraft->isLanded()) {
                    std::cout << "\n  +========================================+\n";
                    std::cout << "  |         SUCCESSFUL LANDING             |\n";
                    std::cout << "  |         Mission accomplished.          |\n";
                    std::cout << "  +========================================+\n";
                    flightRecorder.record("[RESULT] SAFE LANDING. Speed: " + std::to_string(impactSpeed));
                } else {
                    std::cout << "\n  +========================================+\n";
                    std::cout << "  |           SPACECRAFT DESTROYED         |\n";
                    std::cout << "  |       Impact speed too high.           |\n";
                    std::cout << "  +========================================+\n";
                    flightRecorder.record("[RESULT] CRASH. Speed: " + std::to_string(impactSpeed));
                }
                std::cout << "\n  Flight time     : " << std::fixed << std::setprecision(1)
                          << elapsedTime << " s\n";
                std::cout << "  Remaining fuel  : " << std::setprecision(1)
                          << spacecraft->getFuel() << " kg\n\n";
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