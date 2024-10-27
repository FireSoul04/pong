#include "game.hpp"

#include "../game/pong.hpp"

SDL_Window  *Game::s_Window = nullptr;
bool         Game::s_Running = true;
unsigned int Game::s_Width = 0;
unsigned int Game::s_Height = 0;

Game::Game(const std::string& gameTitle, unsigned int width, unsigned int height)
    : m_GameTitle(gameTitle) {
    
    s_Width = width;
    s_Height = height;
}

void Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        forceQuit("Failed to initialize SDL");
    }

    if (TTF_Init() < 0) {
        forceQuit("Failed to initialize SDL_ttf");
    }

    s_Window = SDL_CreateWindow(m_GameTitle.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                s_Width, s_Height,
                                SDL_WINDOW_SHOWN);
    if (!s_Window) {
        forceQuit("Failed to create window");
    }
}

void Game::run() {
    Pong pong;
    Renderer renderer(s_Window);
    Input keyListener;

    unsigned int updates = 0;
    unsigned int frames = 0;
    double deltaTime = 0.0;

    auto lastFrame = system_clock::now();
    auto timer = system_clock::now();

    const double ns = 1.0E9 / m_MaxUpdates;

    pong.init(); // Spawn player, AI and ball
    while (s_Running) {
        deltaTime += (duration_cast<nanoseconds>(system_clock::now() - lastFrame).count()) / ns;
        lastFrame = system_clock::now();
        while (deltaTime >= 1) {
            pong.update(keyListener, deltaTime); // Game logic handler
            updates++;
            deltaTime--;
        }
        pong.loadBuffer(renderer); // Copies all sprites into renderer buffer
        pong.draw(renderer);
        frames++;

        if (system_clock::now() - timer > 1s) {
            timer = system_clock::now();
            SDL_SetWindowTitle(s_Window, std::string(m_GameTitle + " | " + std::to_string(updates) + " ups, " + std::to_string(frames) + " fps").c_str());
            updates = 0;
            frames = 0;
        }

        keyListener.readInput();
    }
}

void Game::quit() {
    SDL_DestroyWindow(s_Window);

    TTF_Quit();
    SDL_Quit();

    Logger::info("Quitting from game");
    std::exit(EXIT_SUCCESS);
}

void Game::forceQuit(const char *errorMsg) {
    SDL_DestroyWindow(s_Window);

    TTF_Quit();
    SDL_Quit();

    Logger::error(errorMsg);
    std::exit(EXIT_FAILURE);
}

const unsigned int Game::width() {
    return s_Width;
}

const unsigned int Game::height() {
    return s_Height;
}