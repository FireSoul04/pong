#pragma once

#include <chrono>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "logger.hpp"
#include "input.hpp"

#include "../render/renderer.hpp"

// Comment this in release
#define DEBUG

using namespace std::chrono;

#ifdef DEBUG
static time_point<system_clock> start;
static double elapsed;
// Only in debug, calculate how many nanoseconds takes to compute a block of code
#define TEST(x) \
    start = system_clock::now(); \
    x; \
    elapsed = duration_cast<nanoseconds>(system_clock::now() - start).count() / 1000.0; \
    Logger::info(std::to_string(elapsed) + "ms")
#else
#define TEST(x) x
#endif

constexpr SDL_Color BLACK = {   0,   0,   0,   0 };
constexpr SDL_Color WHITE = { 255, 255, 255, 255 };

class Game {
public:
    Game(const std::string& gameTitle, unsigned int width, unsigned int height);

    void init();
    void run();

    static void quit();
    static void forceQuit(const char *errorMsg);
    static const unsigned int width();
    static const unsigned int height();

private:
    static SDL_Window  *s_Window;
    static bool         s_Running;
    static unsigned int s_Width;
    static unsigned int s_Height;

    const std::string   m_GameTitle;
    unsigned int        m_MaxUpdates;
};