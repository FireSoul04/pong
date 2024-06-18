#pragma once

#include "../core/vector2.hpp"
#include "../render/sprite.hpp"

static unsigned int ids = 0;

class Entity {
public:
    Entity(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite);
    Entity(const Entity& entity);
    ~Entity();

    const double x() const;
    const double y() const;
    const Vector2 position() const;
    const double speed() const;
    const unsigned int id() const;

    virtual void update(double deltaTime);
    virtual void update();
    
public:
    Sprite sprite;
    Vector2 velocity;

protected:
    Vector2 m_Position;
    double m_Speed;
    unsigned int m_Id;
};