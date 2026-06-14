#ifndef ASTROLANDEXCEPTION_H
#define ASTROLANDEXCEPTION_H

#include <exception>
#include <string>

class AtrolandException : public std::exception {
    private:
        std::string message;
    
    public:
        AtrolandException(const std::string& msg) : message(msg) {}
        
        virtual const char* what() const noexcept override {
            return message.c_str();
        }
};

#endif