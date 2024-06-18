#include "sprite.hpp"

#include "../core/logger.hpp"

Sprite::Sprite(int w, int h, SDL_Color color)
    : m_Color(color) {

    m_Form = { 0, 0, w, h };
    //Logger::info("Sprite created!");
}

Sprite::Sprite(const Sprite& sprite) {
    *this = sprite;
    //Logger::warn("Sprite copied");
}

Sprite::~Sprite() {
    //Logger::info("Sprite destroyed!");
}

const SDL_Rect *Sprite::operator->() const {
    return form();
}

const SDL_Rect *Sprite::form() const {
    return &m_Form;
}

SDL_Color Sprite::color() const {
    return m_Color;
}

void Sprite::move(int x, int y) {
    m_Form.x = x;
    m_Form.y = y;
}