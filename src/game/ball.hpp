#pragma once

#include <SDL.h>
#include <chrono>

#include "entity.hpp"
#include "../core/game.hpp"
#include "../core/vector2.hpp"
#include "../core/random.hpp"
#include "../render/sprite.hpp"

using namespace std::chrono;

class Ball : public Entity {
public:
    Ball(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite);

    void bounce(const Vector2& direction);
    void resetPosition();
    virtual void update(double deltaTime) override;

    const Vector2 randomDirection();

private:
    time_point<system_clock> m_RespawnTimer;
    Vector2                  m_StartPosition;
    bool                     m_Reset = false;
};