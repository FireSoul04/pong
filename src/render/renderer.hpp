#pragma once

#include <vector>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

#include "../config.h"
#include "../core/game.hpp"
#include "../core/logger.hpp"
#include "../game/entity.hpp"
#include "sprite.hpp"

class Renderer {
public:
    Renderer(SDL_Window *window);
    ~Renderer();

    void draw();
    void drawString(const char *str, int x, int y);
    void clear() const;
    void changeColor(const SDL_Color color);
    void loadSprite(const std::shared_ptr<Entity>& entity);
    void loadSprite(const Sprite& sprite);

private:
    void clearBuffer();

private:
    SDL_Renderer       *m_Screen;
    SDL_Texture        *m_Texture;
    TTF_Font           *m_Font;
    std::vector<Sprite> m_Sprites;
};