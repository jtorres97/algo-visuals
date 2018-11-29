#pragma once

#include <string>
#include <iostream>

#define _FILE \
    std::string(strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG(level, message)                                        \
    std::clog << "[" << level << "] " << "<" << _FILE << ">" << " (" << __LINE__ \
              << "): " << message << std::endl;

#define LOG_DEBUG(message) LOG("DEBUG", message)

#define LOG_INFO(message) LOG("INFO", message)

#define LOG_WARNING(message) LOG("WARNING", message) 

#define LOG_ERROR(message) LOG("ERROR", message)
