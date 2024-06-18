#pragma once

#include <vector>
#include <memory>

#include "../core/game.hpp"
#include "../core/vector2.hpp"
#include "entity.hpp"
#include "racket.hpp"
#include "ball.hpp"

enum Entities {
    PLAYER,
    AI,
    BALL,

    MAX_ENTITIES
};

class Pong {
public:
    Pong();

    void init();
    void update(Input& keyListener, const double deltaTime);
    void loadBuffer(Renderer& renderer);
    void draw(Renderer& renderer) const;

    static void addPlayerScore();
    static void addAIScore();
    static unsigned int playerScore();
    static unsigned int AIScore();

private:
    void movePlayer(Input& keyListener);
    void moveAI();
    const std::shared_ptr<Entity> isColliding(const std::shared_ptr<Entity>& entity);

private:
    std::vector<std::shared_ptr<Entity>> m_Entities;
    static unsigned int                  s_PlayerScore;
    static unsigned int                  s_AIScore;
};