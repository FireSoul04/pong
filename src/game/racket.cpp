#include "racket.hpp"

#include <iostream>
#include <string>

Racket::Racket(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite)
    : Entity(position, velocity, speed, sprite) {
}

void Racket::update(double deltaTime) {
    static Vector2 spriteOffset = { sprite->w / 2.0, sprite->h / 2.0 };

    m_Position += velocity * m_Speed * deltaTime;
    if (y() < spriteOffset.y) {
        m_Position.y = spriteOffset.y;
    }
    if (y() > Game::height() - spriteOffset.y) {
        m_Position.y = Game::height() - spriteOffset.y;
    }

    sprite.move(x() - spriteOffset.x, y() - spriteOffset.y);
}