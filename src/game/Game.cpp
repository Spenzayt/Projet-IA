#include "Game.hpp"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

// Game Construtor
Game::Game() : window(VideoMode::getDesktopMode(), "Projet IA", Style::Fullscreen), player(40*2, 40*24, 10) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    grid.loadFromFile("src/map/map.txt");
    enemies.push_back(new Enemy(40*41+5, 40*5+5, 10));
    enemies.push_back(new Enemy(40*41+5, 40*21+5, 100));
}

Game::~Game() {}

// Main Loop
void Game::run() {
    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

// Event Loop
void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
}

// All Update
void Game::update(float deltaTime) {
    player.update(deltaTime, grid, enemies);
    for (auto& enemy : enemies) {
        enemy->update(deltaTime, grid, { &player });
    }
}

// All Draw
void Game::render() {
    window.clear();

    grid.draw(window);
    player.draw(window);
    for (const auto& enemy : enemies) {
        if (enemy->isAlive()) {
            enemy->draw(window);
        }
    }
    window.display();
}