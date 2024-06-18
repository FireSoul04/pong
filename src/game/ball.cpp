#include "ball.hpp"

#include "pong.hpp"

Ball::Ball(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite)
    : Entity(position, velocity, speed, sprite), m_StartPosition(position) {

    this->velocity = randomDirection();
}

void Ball::bounce(const Vector2& direction) {
    velocity = Vector2::reflect(velocity, direction);
}

void Ball::resetPosition() {
    velocity = randomDirection();
    m_Position = m_StartPosition;
}

void Ball::update(double deltaTime) {
    Vector2 spriteOffset = { sprite->w / 2.0, sprite->h / 2.0 };

    m_Position += velocity * m_Speed * deltaTime;

    // This should handle score
    if (x() < spriteOffset.x) {
        resetPosition();
        Pong::addAIScore();
    } else if (x() > Game::width() - spriteOffset.x) {
        resetPosition();
        Pong::addPlayerScore();
    }

    if (y() < spriteOffset.y) {
        m_Position.y = spriteOffset.y;
        bounce(Vector2::i());
    } else if (y() > Game::height() - spriteOffset.y) {
        m_Position.y = Game::height() - spriteOffset.y;
        bounce(Vector2::i());
    }

    sprite.move(x() - spriteOffset.x, y() - spriteOffset.y);
}

const Vector2 Ball::randomDirection() {
    Vector2 direction = { Random::generateDouble(-1.0, 1.0), 0.4 * Random::generateDouble(-1.0, 1.0) };
    direction.normalize();
    return direction;
}