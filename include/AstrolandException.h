#ifndef ASTROLANDEXCEPTION_H
#define ASTROLANDEXCEPTION_H

#include <exception>
#include <string>

class AstrolandException : public std::exception {
    private:
        std::string message;
    
    public:
        AstrolandException(const std::string& msg) : message(msg) {}
        
        const char* what() const noexcept override {
            return message.c_str();
        }
};

#endif