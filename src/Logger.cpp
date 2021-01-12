#include "Logger.h"

#include <iostream>
#include <string>

void Logger::Log(const std::string& message) {
    std::cout << message << std::endl;
}

void Logger::Error(const std::string& message) {
    std::cout << message << std::endl;
}
