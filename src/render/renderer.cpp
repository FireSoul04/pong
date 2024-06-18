#include "renderer.hpp"

#include "../game/pong.hpp"

Renderer::Renderer(SDL_Window *window) {
    m_Screen = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    if (!m_Screen) {
        Game::forceQuit("Failed to create renderer");
    }
    m_Font = TTF_OpenFont(ASSETS_PATH"font.ttf", 48);
    if (!m_Font) {
        Game::forceQuit("Failed to create font");
    }
    m_Sprites.reserve(MAX_ENTITIES + 1);
}

Renderer::~Renderer() {
    TTF_CloseFont(m_Font);
    SDL_DestroyTexture(m_Texture);
    SDL_DestroyRenderer(m_Screen);
}

void Renderer::draw() {
    for (const Sprite& s : m_Sprites) {
        changeColor(s.color());
        SDL_RenderFillRect(m_Screen, s.form());
    }
    SDL_RenderPresent(m_Screen);
    
    clearBuffer();
}

void Renderer::drawString(const char *str, int x, int y) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(m_Font, str, WHITE);
    if (!textSurface) {
        Game::forceQuit("Failed to create surface");
    }
    m_Texture = SDL_CreateTextureFromSurface(m_Screen, textSurface);
    if (!m_Texture) {
        Game::forceQuit("Failed to create texture");
    }
    SDL_FreeSurface(textSurface);

    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(m_Texture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect renderQuad = { x, y, textWidth, textHeight };

    SDL_RenderCopy(m_Screen, m_Texture, nullptr, &renderQuad);
    SDL_DestroyTexture(m_Texture);
}

void Renderer::clear() const {
    SDL_RenderClear(m_Screen);
}

void Renderer::changeColor(const SDL_Color color) {
    SDL_SetRenderDrawColor(m_Screen, color.r, color.g, color.b, color.a);
}

void Renderer::loadSprite(const std::shared_ptr<Entity>& entity) {
    m_Sprites.emplace_back(entity->sprite);
}

void Renderer::loadSprite(const Sprite& sprite) {
    m_Sprites.emplace_back(sprite);
}

void Renderer::clearBuffer() {
    m_Sprites.clear();
}