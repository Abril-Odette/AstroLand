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

static void printSeparator() {
    std::cout << "  +----------------------------------------+\n";
}

static void printAltitudeBar(double altitude, double maxAlt) {
  const int BAR_HEIGHT = 12;
    int level = 0;
    if (maxAlt > 0)
        level = static_cast<int>((altitude / maxAlt) * BAR_HEIGHT);
    if (level > BAR_HEIGHT) level = BAR_HEIGHT;
    if (level < 0)          level = 0;

    std::cout << "  |  ALT  |  STATUS\n";
    for (int i = BAR_HEIGHT; i >= 0; --i) {
        if (i == BAR_HEIGHT)
            std::cout << "  | " << std::setw(5) << static_cast<int>(maxAlt) << " |";
        else if (i == BAR_HEIGHT / 2)
            std::cout << "  | " << std::setw(5) << static_cast<int>(maxAlt / 2) << " |";
        else if (i == 0)
            std::cout << "  |     0 |";
        else
            std::cout << "  |       |";

        if (i == level)
            std::cout << "  [^] spacecraft\n";
        else if (i == 0)
            std::cout << "  === surface ===\n";
        else
            std::cout << "\n";
    }
}

static void printFuelBar(double fuel, double maxFuel) {
    const int WIDTH = 24;
    int filled = (maxFuel > 0) ? static_cast<int>((fuel / maxFuel) * WIDTH) : 0;
    if (filled < 0) filled = 0;
    std::cout << "  Fuel  [";
    for (int i = 0; i < WIDTH; ++i)
        std::cout << (i < filled ? '#' : '.');
    std::cout << "] " << std::fixed << std::setprecision(1) << fuel << " kg\n";
}

static std::string speedStatus(double speed, double altitude) {
    if (altitude < 200.0 && speed > 5.0)  return "  *** DANGER: BRAKE NOW ***";
    if (altitude < 500.0 && speed > 20.0) return "  !! High speed near surface !!";
    if (altitude < 1000.0)                return "  Approaching surface - prepare to brake";
    return "  Cruising";
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

static void printControls() {
    std::cout << "\n";
    std::cout << "  +-------------- CONTROLS ---------------+\n";
    std::cout << "  |  [t] + Enter  ->  Fire thruster       |\n";
    std::cout << "  |  [s] + Enter  ->  Cut thruster        |\n";
    std::cout << "  |  [Enter]      ->  Coast (no thrust)   |\n";
    std::cout << "  |  [q] + Enter  ->  Abort mission       |\n";
    std::cout << "  +---------------------------------------+\n";
    std::cout << "  TIP: The thruster fires UPWARD to slow  \n";
    std::cout << "  your descent. Use short burns near the  \n";
    std::cout << "  surface. Safe landing speed: <= 5 m/s.  \n";
    printSeparator();
}

static void printIntro(const std::string& bodyName, double gravity) {
    clearScreen();
    std::cout << "\n";
    std::cout << "  +========================================+\n";
    std::cout << "  |         A S T R O L A N D             |\n";
    std::cout << "  |     Space Landing Simulator            |\n";
    std::cout << "  +========================================+\n\n";
    std::cout << "  MISSION BRIEFING\n";
    printSeparator();
    std::cout << "  Target body    : " << bodyName << "\n";
    std::cout << "  Surface gravity: " << std::fixed << std::setprecision(2)
              << gravity << " m/s^2\n";
    std::cout << "  Starting alt.  : 3500 m\n";
    std::cout << "  Ship mass      : 500 kg\n";
    std::cout << "  Fuel loaded    : 800 kg\n";
    std::cout << "  Thruster force : 15000 N (upward)\n";
    std::cout << "  Fuel burn rate : 8 kg/s\n";
    printSeparator();
    std::cout << "\n";
    std::cout << "  OBJECTIVE: Land the spacecraft safely.\n";
    std::cout << "  Touch down at 5 m/s or less to survive.\n";
    std::cout << "  Exceed that and the ship is destroyed.\n";
    printControls();
    std::cout << "  Press Enter to begin the mission...";
    std::cin.ignore();
}

void Game::run() {

  try {
    printIntro(astro->getName(), astro->surfaceGravity());
        flightRecorder.record("[GAME] Game started.");

    const double dt = 0.05; 
    const double STEP_SECS  = 1.0;
    const int    PHYS_STEPS = static_cast<int>(STEP_SECS / dt);
    const double MAX_ALT    = 3500.0;
    const double INIT_FUEL  = 800.0;

    double elapsedTime = 0.0;
    std::string lastCmd = "none";
        std::string lastMsg = "";

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
            std::cout << "  +========= ASTROLAND SIMULATOR =========+\n";
            std::cout << "  | Mission: Land on " << std::left << std::setw(21)
                      << astro->getName() << " |\n";
            std::cout << "  +=======================================+\n\n";

            // Telemetry
            std::cout << "  --------- TELEMETRY --------------------\n";
            std::cout << std::right;
            std::cout << "  Time       : " << std::fixed << std::setprecision(1)
                      << elapsedTime << " s\n";
            std::cout << "  Altitude   : " << std::setprecision(1)
                      << altitude << " m\n";
            std::cout << "  Vert. vel. : " << std::setprecision(2) << vy << " m/s  "
                      << (vy < -0.1 ? "[descending]" : vy > 0.1 ? "[ascending] " : "[stable]    ")
                      << "\n";
            std::cout << "  Speed      : " << std::setprecision(2) << speed << " m/s\n";
            std::cout << "  Gravity    : " << std::setprecision(2)
                      << astro->surfaceGravity() << " m/s^2\n";
            std::cout << "  Thruster   : "
                      << (burning ? "[ON]  FIRING - consuming fuel" : "[OFF] idle") << "\n";
            printFuelBar(fuel, INIT_FUEL);
            std::cout << "  Status     : " << speedStatus(speed, altitude) << "\n\n";

            printAltitudeBar(altitude, MAX_ALT);
            std::cout << "\n";
            std::cout << "  ========================================\n";
            std::cout << "  Command> ";

            //feedback
            std::cout << "  Last action : " << lastCmd << "\n";
            if (!lastMsg.empty())
                std::cout << "  >> " << lastMsg << "\n";
            std::cout << "\n";

            //controlls
            std::cout << "  --------- CONTROLS ---------------------\n";
            std::cout << "  [t] Fire thruster (upward burn)  ";
            std::cout << (burning ? "<-- ACTIVE\n" : "\n");
            std::cout << "  [s] Cut thruster\n";
            std::cout << "  [Enter] Coast for 0.5 seconds\n";
            std::cout << "  [q] Abort mission\n";
            std::cout << "  Safe landing speed: <= 5.0 m/s\n";
            std::cout << "  ----------------------------------------\n";
            std::cout << "  Command> ";

            std::string line;
            std::getline(std::cin, line);
            char cmd = line.empty() ? ' ' : line[0];

            if (cmd == 'q') {
                std::cout << "\n  Mission aborted by pilot.\n";
                flightRecorder.record("[GAME] Mission aborted by user.");
                flightRecorder.saveLogsToFile();
                std::cout << "  Flight log saved to logs/flight.log\n\n";
                return;
            }

            // Aplicar comando y guardar feedback
            if (cmd == 't') {
                spacecraft->setThrusterActive(true);
                lastCmd = "[t] Fire thruster";
                lastMsg = "Thruster ON - burning " +
                          std::to_string(static_cast<int>(8.0 * STEP_SECS)) +
                          " kg of fuel this step";
                flightRecorder.record("[CMD] Thruster ON at t=" + std::to_string(elapsedTime));
            } else if (cmd == 's') {
                spacecraft->setThrusterActive(false);
                lastCmd = "[s] Cut thruster";
                lastMsg = "Thruster OFF - coasting under gravity";
                flightRecorder.record("[CMD] Thruster OFF at t=" + std::to_string(elapsedTime));
            } else {
                lastCmd = "[Enter] Coast";
                lastMsg = "Coasting - gravity pulling at " +
                          [&]() {
                              std::ostringstream o;
                              o << std::fixed << std::setprecision(2)
                                << astro->surfaceGravity();
                              return o.str();
                          }() + " m/s^2";
            }

            bool finished = false;
            for (int i = 0; i < PHYS_STEPS && !finished; ++i) {
                spacecraft->update(*astro, dt);
                elapsedTime += DT;
                if (spacecraft->checkLanding(*astro))
                    finished = true;
            }

            std::ostringstream oss;
            oss << "[STEP] t=" << std::fixed << std::setprecision(1) << elapsedTime
                << " alt=" << std::setprecision(0) << altitude
                << " spd=" << std::setprecision(2) << speed
                << " fuel=" << std::setprecision(1) << fuel
                << (burning ? " BURN" : " COAST");
            flightRecorder.record(oss.str());

            if (finished) {
                clearScreen();
                double impactSpeed = speed;
                
                printSeparator();
                if (spacecraft->isLanded()) {
                    std::cout << "\n";
                    std::cout << "  +========================================+\n";
                    std::cout << "  |          SUCCESSFUL LANDING            |\n";
                    std::cout << "  |          Mission accomplished.         |\n";
                    std::cout << "  +========================================+\n";
                    flightRecorder.record("[RESULT] SAFE LANDING.");
                } else {
                    std::cout << "\n";
                    std::cout << "  +========================================+\n";
                    std::cout << "  |          SPACECRAFT DESTROYED          |\n";
                    std::cout << "  |      Impact velocity too high.         |\n";
                    std::cout << "  +========================================+\n";
                    flightRecorder.record("[RESULT] CRASH.");
                }

                std::cout << "\n";
                printSeparator();
                std::cout << "  FLIGHT SUMMARY\n";
                printSeparator();
                std::cout << "  Flight time      : " << std::fixed << std::setprecision(1)
                          << elapsedTime << " s\n";
                std::cout << "  Impact speed     : " << std::setprecision(2)
                          << speed << " m/s"
                          << (spacecraft->isLanded() ? "  (safe)" : "  (fatal)") << "\n";
                std::cout << "  Remaining fuel   : " << std::setprecision(1)
                          << spacecraft->getFuel() << " kg\n";
                std::cout << "  Fuel used        : " << std::setprecision(1)
                          << (INIT_FUEL - spacecraft->getFuel()) << " kg\n";
                printSeparator();
                std::cout << "\n";
                flightRecorder.record("[SUMMARY] t=" + std::to_string(elapsedTime) +
                                      " fuel_remaining=" + std::to_string(spacecraft->getFuel()));
                break;
            }
        }

    flightRecorder.saveLogsToFile();
    std::cout << "Game ended. Flight log saved." << std::endl;

  } catch (const AstrolandException& ex) {
        std::cerr << "[AstroLandException]: " << ex.what() << std::endl;
        flightRecorder.record(std::string("[ERROR] ") + ex.what());
        flightRecorder.saveLogsToFile();
    } catch (const std::exception& ex) {
        std::cerr << "[std::exception]: " << ex.what() << std::endl;
        flightRecorder.record(std::string("[ERROR] Unexpected: ") + ex.what());
        flightRecorder.saveLogsToFile();
    }
};