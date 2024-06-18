#pragma once

#include <memory>
#include <SDL.h>

#include "game.hpp"

#define SIZE 120

class Input {
public:
    Input();

    bool isPressed(SDL_Keycode key);
    void readInput();

private:
    void pressedKeys(SDL_Keycode key);
    void releasedKeys(SDL_Keycode key);

private:
    bool m_KeysState[SIZE];
    SDL_Event m_Event;
};