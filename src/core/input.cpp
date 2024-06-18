#include "input.hpp"

Input::Input() {
    memset(m_KeysState, false, SIZE);
}

bool Input::isPressed(SDL_Keycode key) {
    return m_KeysState[key];
}

void Input::pressedKeys(SDL_Keycode key) {
    switch (key) {
    case SDLK_w:
    case SDLK_s:
    case SDLK_SPACE:
        m_KeysState[key] = true;
        break;
    }
}

void Input::releasedKeys(SDL_Keycode key) {
    switch (key) {
    case SDLK_w:
    case SDLK_s:
    case SDLK_SPACE:
        m_KeysState[key] = false;
        break;
    }
}

void Input::readInput() {
    while (SDL_PollEvent(&m_Event)) {
        switch (m_Event.type) {
        case SDL_QUIT:
            Game::quit();
            break;
        case SDL_KEYDOWN:
            pressedKeys(m_Event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            releasedKeys(m_Event.key.keysym.sym);
            break;
        }
    }
}