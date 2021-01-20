#include "stdoutlogger.h"


void StdoutLogger::info(std::string message)
{
    std::cout << "[info   ] " << message << std::endl;
}

void StdoutLogger::debug(std::string message)
{
    std::cout << "[debug  ] " << message << std::endl;
}

void StdoutLogger::warning(std::string message)
{
    std::cout << "[warning] " << message << std::endl;
}

void StdoutLogger::error(std::string message)
{
    std::cout << "[error  ] " << message << std::endl;
}
