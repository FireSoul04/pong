#pragma once

#include <SDL.h>

#include "entity.hpp"
#include "../core/game.hpp"
#include "../core/vector2.hpp"
#include "../core/random.hpp"
#include "../render/sprite.hpp"

class Ball : public Entity {
public:
    Ball(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite);

    void bounce(const Vector2& direction);
    void resetPosition();
    virtual void update(double deltaTime) override;

    const Vector2 randomDirection();

private:
    Vector2 m_StartPosition;
};