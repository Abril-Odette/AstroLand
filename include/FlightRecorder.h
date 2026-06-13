#ifndef FLIGHT_RECORDER_H
#define FLIGHT_RECORDER_H

#include <vector>
#include <string>

class FlightRecorder {
    private:
        std::vector<std::string> logs;
        std::string logFilePath;

    public:
        FlightRecorder(const std::string& filePath) : logFilePath(filePath) {}

        void record(const std::string& message);
        void printLogs() const;
        void saveLogsToFile() const;
    
};

#endif