#pragma once

#include <iostream>
#include <ctime>
#include <map>

#include "game.hpp"

enum class Colors {
    BLUE,
    YELLOW,
    RED,
    BLANK,

    COLORS
};

class Logger {
public:
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
    static const std::string colorString(Colors color);
    static const std::string getTime();

private:
    Logger();

public:
    static std::map<Colors, const std::string> s_ColorToString;
};