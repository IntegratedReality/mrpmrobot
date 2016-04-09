#pragma once

#include <exception>

class SetupGpioException : public std::exception
{
public:
    const char* what() const noexcept override; 
};
