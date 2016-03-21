
#include "gpioerror.h"

const char* SetupGpioException::what() const noexcept
{
    return "failed in SetupGpio";
}
