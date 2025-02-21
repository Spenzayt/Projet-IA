#include "Game.hpp"

// Game Constructor
Game::Game()
    : window(VideoMode::getDesktopMode(), "Projet IA", Style::Fullscreen),
    player(40 * 2, 40 * 24, 10)
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // Load the map
    grid.loadFromFile("src/script/output_map.txt");

    // Create enemies with their positions and health points
    enemies.push_back(make_unique<Enemy>(40 * 4 + 5, 40 * 4 + 5, 100));
    enemies.push_back(make_unique<Enemy>(40 * 4 + 5, 40 * 22 + 5, 10));
    enemies.push_back(make_unique<Enemy>(40 * 43 + 5, 40 * 4 + 5, 100));
    enemies.push_back(make_unique<Enemy>(40 * 43 + 5, 40 * 22 + 5, 10));
}

// Game Destructor
Game::~Game() {}

// Main game loop
void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

// Handle events
void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
}

// Update all game objects
void Game::update(float deltaTime) {
    // Create a vector of entity pointers (Player + Enemies)
    vector<Entity*> entities;
    entities.push_back(&player);
    for (auto& enemy : enemies) {
        entities.push_back(enemy.get());  // Add the enemy using get() to get the pointer
    }

    // Update the player
    player.update(deltaTime, grid, entities);

    // Update each enemy
    for (auto& enemy : enemies) {
        enemy->update(deltaTime, grid, entities);
    }
}

// Render all game objects
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