#include "logger.hpp"

#ifdef DEBUG
#define LOG(x) std::cout << "[ " << getTime() << " ]" << x << '\n'
#else
#define LOG(x)
#endif

std::map<Colors, const std::string> Logger::s_ColorToString = {
    { Colors::RED, "\033[31m" },
    { Colors::BLUE, "\033[96m" },
    { Colors::YELLOW, "\033[93m" },
    { Colors::BLANK, "\033[m" }
};

const std::string Logger::colorString(Colors color) {
    return s_ColorToString.at(color);
}

const std::string Logger::getTime() {
    time_t now = std::time(nullptr);
    struct tm *time = std::localtime(&now);
    char s[15];
    sprintf(s, "%02d:%02d:%02d", time->tm_hour, time->tm_min, time->tm_sec);

    return std::string(s);
}

void Logger::info(const std::string& msg) {
    LOG(colorString(Colors::BLUE) << " [INFO] " << msg << colorString(Colors::BLANK));
}

void Logger::warn(const std::string& msg) {
    LOG(colorString(Colors::YELLOW) << " [WARNING] " << msg << colorString(Colors::BLANK));
}

void Logger::error(const std::string& msg) {
    LOG(colorString(Colors::RED) << " [ERROR] " << msg << colorString(Colors::BLANK));
}
