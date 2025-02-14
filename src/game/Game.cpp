#include "Game.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game() : window(sf::VideoMode::getDesktopMode(), "Behavior Tree"), player(200.f, 400.f)
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.create(sf::VideoMode::getDesktopMode(), "Behavior Tree", sf::Style::Fullscreen);

    grid.loadFromFile("src/map/map.txt");
    enemies = { Enemy(100, 100), Enemy(700, 100) };
}

Game::~Game() {}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
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
