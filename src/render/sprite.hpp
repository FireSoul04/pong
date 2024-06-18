#pragma once

#include <memory>
#include <SDL.h>

class Sprite {
public:
    Sprite(int w, int h, SDL_Color color);
    Sprite(const Sprite& sprite);
    ~Sprite();

    SDL_Color color() const;
    void move(int x, int y);

    const SDL_Rect *operator->() const;
    const SDL_Rect *form() const;

private:
    SDL_Rect  m_Form;
    SDL_Color m_Color;
};