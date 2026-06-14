#include "FlightRecorder.h"

#include <fstream>
#include <iostream>

FlightRecorder::FlightRecorder(const std::string& logFilePath) : logFilePath(logFilePath) {}

void FlightRecorder::record(const std::string& message) {
    logs.push_back(message);
}   

void FlightRecorder::printLogs() const {
    for (const auto& log : logs) {
        std::cout << log << std::endl;
    }
}   

void FlightRecorder::saveLogsToFile() const {
    std::ofstream outFile(logFilePath);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << logFilePath << std::endl;
        return;
    }
    for (const std::string& log : logs) {
        outFile << log << std::endl;
    }
}