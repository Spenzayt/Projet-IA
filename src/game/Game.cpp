#include "Game.hpp"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

Game::Game() : window(VideoMode::getDesktopMode(), "Projet IA", Style::Fullscreen), player(200.f, 400.f, 10)
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    grid.loadFromFile("src/map/map.txt");
    enemies.push_back(new Enemy(40*41, 40*5, 10));
    enemies.push_back(new Enemy(40*41, 40*21, 100));
}

Game::~Game() {}

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

void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime, grid, enemies);
    for (auto& enemy : enemies) {
        enemy->update(deltaTime, grid, { &player });
    }
}

void Game::render() {
    window.clear();

    grid.draw(window);
    window.draw(player.sprite);
    for (const auto& enemy : enemies) {
        if (enemy->isAlive()) {
            window.draw(enemy->sprite);
        }
    }
    window.display();
}