#pragma once

#include <SDL.h>

#include "entity.hpp"
#include "../core/game.hpp"
#include "../core/vector2.hpp"
#include "../render/sprite.hpp"

class Racket : public Entity {
public:
    Racket(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite);

    virtual void update(double deltaTime) override;
};