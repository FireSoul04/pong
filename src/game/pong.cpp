#include "pong.hpp"

const double MAX_ANGLE = M_PI / 2;

unsigned int Pong::s_PlayerScore = 0;
unsigned int Pong::s_AIScore = 0;

Pong::Pong() {
    m_Entities.reserve(MAX_ENTITIES);
}

void Pong::init() {
    const Vector2 leftSide = { 10.0, Game::height() / 2 };
    const Vector2 rightSide = { Game::width() - 10.0, Game::height() / 2 };
    const Vector2 center = { Game::width() / 2, Game::height() / 2 };

    const Vector2 racketVelocity = Vector2::zero();
    const double racketSpeed = 10.0;
    const Sprite racketSprite(8, 60, WHITE);

    const Vector2 ballVelocity = Vector2::zero();
    const double ballSpeed = 15.0;
    const Sprite ballSprite(10, 10, WHITE);

    m_Entities.emplace_back(std::make_shared<Racket>(leftSide, racketVelocity, racketSpeed, racketSprite));
    m_Entities.emplace_back(std::make_shared<Racket>(rightSide, racketVelocity, racketSpeed, racketSprite));
    m_Entities.emplace_back(std::make_shared<Ball>(center, ballVelocity, ballSpeed, ballSprite));
}

void Pong::movePlayer(Input& keyListener) {
    Vector2 velocity = Vector2::zero();
    std::shared_ptr<Entity>& player = m_Entities[PLAYER];
    /*if (keyListener.isPressed(SDLK_w)) {
        velocity.y -= 1.0;
    }
    if (keyListener.isPressed(SDLK_s)) {
        velocity.y += 1.0;
    }*/
    std::shared_ptr<Entity>& ball = m_Entities[BALL];

    if (fabs(player->x() - ball->x()) < Game::width() / 2) {
        if (player->y() < ball->y()) {
            velocity.y += 1.0;
        }
        if (player->y() > ball->y()) {
            velocity.y -= 1.0;
        }
        if (fabs(player->y() - ball->y()) < player->sprite->h / 2) {
            velocity = Vector2::zero();
        }
    } else {
        velocity = Vector2::zero();
    }
    player->velocity = velocity;
}

void Pong::moveAI() {
    Vector2 velocity = Vector2::zero();
    std::shared_ptr<Entity>& ball = m_Entities[BALL];
    std::shared_ptr<Entity>& ai = m_Entities[AI];

    if (fabs(ai->x() - ball->x()) < Game::width() / 2) {
        if (ai->y() < ball->y()) {
            velocity.y += 1.0;
        }
        if (ai->y() > ball->y()) {
            velocity.y -= 1.0;
        }
        if (fabs(ai->y() - ball->y()) < ai->sprite->h / 2) {
            velocity = Vector2::zero();
        }
    } else {
        velocity = Vector2::zero();
    }
    ai->velocity = velocity;
}

// standard fabs is slow, so i wrote mine
static double myFabs(double x) {
    uint64_t i = *(uint64_t *)&x;
    uint64_t mask = 0x7FFFFFFFFFFFFFFFUL; // Sets the floating point sign bit to 0
    i &= mask;
    x = *(double *)&i;
    return x;
}

const std::shared_ptr<Entity> Pong::isColliding(const std::shared_ptr<Entity>& entity) {
    for (std::shared_ptr<Entity>& e : m_Entities) {
        if (e != entity) {
            const Sprite rect1 = e->sprite;
            const Sprite rect2 = entity->sprite;
            if (rect1->x + rect1->w >= rect2->x - rect2->w &&
                rect1->x <= rect2->x + rect2->w + rect2->w &&
                rect1->y + rect1->h >= rect2->y - rect2->h &&
                rect1->y <= rect2->y + rect2->h + rect2->h) {
                
                return e;
            }
        }
    }
    return nullptr;
}

void Pong::update(Input& keyListener, const double deltaTime) {
    movePlayer(keyListener);
    moveAI();
    for (std::shared_ptr<Entity>& e : m_Entities) {
        e->update(deltaTime);
    }

    std::shared_ptr<Ball> ball = std::static_pointer_cast<Ball>(m_Entities[BALL]);
    std::shared_ptr<Entity> collidingEntity = isColliding(ball);
    if (collidingEntity != nullptr) {
        const double racketOffset = collidingEntity->sprite->h / 2;
        const double intersect = collidingEntity->sprite->y + racketOffset - ball->sprite->y;
        const double normalizedIntersect = intersect / racketOffset;
        const double angle = MAX_ANGLE * normalizedIntersect;

        ball->velocity.x = cos(angle);
        ball->velocity.y = -sin(angle);
    }
}

void Pong::loadBuffer(Renderer& renderer) {
    Sprite halfScreen(2, Game::height(), WHITE);
    halfScreen.move(Game::width() / 2, 0);
    for (std::shared_ptr<Entity>& e : m_Entities) {
        renderer.loadSprite(e);
    }
    renderer.loadSprite(halfScreen);
}

void Pong::draw(Renderer& renderer) const {
    unsigned int textPositionX = Game::width() / 2 - 16;
    unsigned int textPositionY = 24;
    unsigned int textOffsetX = 128;

    std::string playerScore = std::to_string(s_PlayerScore);
    std::string AIScore = std::to_string(s_AIScore);

    renderer.changeColor(BLACK);
    renderer.clear();
    renderer.changeColor(WHITE);
    renderer.drawString(playerScore.c_str(), textPositionX - textOffsetX, textPositionY);
    renderer.drawString(AIScore.c_str(), textPositionX + textOffsetX, textPositionY);
    renderer.draw();
}

void Pong::addPlayerScore() {
    s_PlayerScore++;
}

void Pong::addAIScore() {
    s_AIScore++;
}

unsigned int Pong::playerScore() {
    return s_PlayerScore;
}

unsigned int Pong::AIScore() {
    return s_AIScore;
}