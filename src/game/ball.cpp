#include "ball.hpp"

#include "pong.hpp"

Ball::Ball(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite)
    : Entity(position, velocity, speed, sprite), m_StartPosition(position) {

    resetPosition();
}

void Ball::bounce(const Vector2& direction) {
    velocity = Vector2::reflect(velocity, direction);
}

void Ball::resetPosition() {
    velocity = randomDirection();
    m_Position = m_StartPosition;
    m_RespawnTimer = system_clock::now();
    m_Reset = true;
}

void Ball::update(double deltaTime) {
    Vector2 spriteOffset = { sprite->w / 2.0, sprite->h / 2.0 };
    auto timeElapsed = system_clock::now() - m_RespawnTimer;

    if (!m_Reset) {
        m_Position += velocity * m_Speed * deltaTime;
    } else if (timeElapsed > 0s) {
        m_Reset = false;
    }

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
    int sign = 2 * Random::generate(0, 1) - 1;
    Vector2 direction = { sign * Random::generateDouble(0.5, 1.0), Random::generateDouble(-1.0, 1.0) };
    direction.normalize();
    return direction;
}