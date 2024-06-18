#include "entity.hpp"
#include "../core/logger.hpp"

Entity::Entity(const Vector2& position, const Vector2& velocity, const double speed, const Sprite& sprite)
    : sprite(sprite), velocity(velocity), m_Position(position), m_Speed(speed) {
    
    m_Id = ids;
    ids++;
    Logger::info("Entity " + std::to_string(m_Id) + " created!");
}

Entity::Entity(const Entity& entity)
    : sprite(entity.sprite), velocity(entity.velocity), m_Position(entity.m_Position), m_Speed(entity.m_Speed) {
    
    Logger::warn("Entity " + std::to_string(m_Id) + " copied!");
}

Entity::~Entity() {
    Logger::info("Entity " + std::to_string(m_Id) + " destroyed!");
}

const double Entity::x() const {
    return m_Position.x;
}

const double Entity::y() const {
    return m_Position.y;
}

const Vector2 Entity::position() const {
    return m_Position;
}

const double Entity::speed() const {
    return m_Speed;
}

const unsigned int Entity::id() const {
    return m_Id;
}

void Entity::update(double deltaTime) {
    m_Position += velocity * m_Speed * deltaTime;
    sprite.move(x() - sprite->w / 2, y() - sprite->h / 2);
}

void Entity::update() {
    m_Position += velocity * m_Speed;
    sprite.move(x() - sprite->w / 2, y() - sprite->h / 2);
}