#include "Game.h"
#include <iostream>

Game::Game(const std::string &config) { init(config); }

void Game::init(const std::string &path) {
    // TODO read config fiel here,
    // use the premade PlayerConfig, EnemyConfig, BulletConfig Variables

    m_window.create(sf::VideoMode({1280, 720}), "Galaxy Wars");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}
