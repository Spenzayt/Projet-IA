#include "Game.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game() : window(VideoMode::getDesktopMode(), "Projet IA"), player(200.f, 400.f)
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.create(VideoMode::getDesktopMode(), "Projet IA", Style::Fullscreen);

    grid.loadFromFile("src/map/map.txt");
    enemies = { Enemy(100, 100), Enemy(700, 100) };
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
    player.update(deltaTime, grid);
    for (auto& enemy : enemies) {
        enemy.update(deltaTime, grid);
    }
}

void Game::render() {
    window.clear();

    grid.draw(window);
    window.draw(player.shape);
    for (const auto& enemy : enemies)
        window.draw(enemy.shape);

    window.display();
}