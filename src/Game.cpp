#include "Game.h"
#include "Components.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <iostream>
#include <memory>

Game::Game(const std::string &config) { init(config); }

void Game::init(const std::string &path) {
    // TODO read config file here,
    // use the premade PlayerConfig, EnemyConfig, BulletConfig Variables
    //
    // Changes the rand seed to spawn different "random" enemies
    srand(time(0));

    m_window = sf::RenderWindow(sf::VideoMode({1280, 720}), "Galaxy Wars");
    m_window.setFramerateLimit(60);

    spawnPlayer();
    m_running = true;
}

void Game::run() {
    while (m_running) {

        m_entityManager.update();

        if (!m_paused) {
            sEnemySpawner();
            sMovement();
            sEnemyMovement();
            sBulletMovement();
            // sCollision();
        }

        sUserInput();
        sRender();

        m_currentFrame++;
    }
    m_window.close();
}

void Game::setPaused(bool paused) { m_paused = paused; }

void Game::spawnPlayer() {

    // TODO Finish adding all properties of the player with the correct values
    // from the config

    auto entity = m_entityManager.addEntity("player");

    entity->add<CTransform>(Vec2(200.f, 200.f), Vec2(1.f, 1.f), 0.0f);

    entity->add<CShape>(32.f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0),
                        4.f);

    entity->add<CInput>();

    m_player = entity;
}

void Game::spawnEnemy() {

    // TODO: Spawn Enemy with random sizes and random colors and random speed

    auto entity = m_entityManager.addEntity("enemy");

    auto windowWidth = m_window.getSize().x;
    auto windowHeight = m_window.getSize().y;

    auto positionX = rand() % windowWidth + 1.f;
    auto positionY = rand() % windowHeight + 1.f;

    auto radius = rand() % 32 + 1.f;

    entity->add<CTransform>(Vec2(positionX + radius, positionY + radius),
                            Vec2(1.f, 1.f), 0.0f);

    entity->add<CShape>(radius, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0),
                        4.f);

    entity->add<CInput>();

    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e) {
    // TODO:
    //  spawn small enemies at the location of the input enemy entity
    //  when we create the smaller enemy, we have to read the values of the
    //  original enemy spawn a number of small enemies equal to the vertices of
    //  the original enemy set each small enemy to the same color as the
    //  original, half the size small enemies are worth double the points of the
    //  original enemey
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target) {
    // implement the spawning of a bullet which travels toward target
    // bullet speed is given as a sclar speed
    // you must set the velocity by using formula in notes
    //
    // cos(zeta) = X / R
    // sin(zeta) = Y / R
    // Vec2 velocity (S*cos(o), S*sin(o)) S = speed;
    //
    // TODO: Implement a bullet that starts at entity and travels to target
    auto bullet = m_entityManager.addEntity("bullet");

    auto distance = target - entity->get<CTransform>().pos;

    std::cout << "Target X: " << distance.x << std::endl;
    std::cout << "Target Y: " << distance.y << std::endl;

    distance.normalize();

    std::cout << "Normalized Target X: " << distance.x << std::endl;
    std::cout << "Normalized Target Y: " << distance.y << std::endl;
    // auto angle = std::atan2f(distance.y, distance.x);
    // auto angleDegrees = angle * 180.f / M_PI;
    //
    auto speed = 10.f;

    Vec2 velocity = Vec2(speed * distance.x, speed * distance.y);

    bullet->add<CTransform>(entity->get<CTransform>().pos, velocity, 0);
    bullet->add<CShape>(10, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0),
                        2);
}

void Game::sRender() {
    m_window.clear();

    for (auto e : m_entityManager.getEntities()) {
        auto shape = e->get<CShape>();
        auto transform = e->get<CTransform>();

        // m_player->cTransform->angle += 1.0f;
        shape.circle.setPosition({transform.pos.x, transform.pos.y});
        // shape.circle.setRotation(sf::degrees(transform.angle));

        m_window.draw(shape.circle);
    }

    m_window.display();
}

void Game::sMovement() {

    int speed = 5;
    // Player Movement
    //  reset velocity to 0 before adding speed again
    m_player->get<CTransform>().velocity = {0, 0};

    switch (m_player->get<CInput>().currentInput) {
    case EInput::UP:
        m_player->get<CTransform>().velocity.y = -5;
        break;
    case EInput::DOWN:
        m_player->get<CTransform>().velocity.y = 5;
        break;
    case EInput::LEFT:
        m_player->get<CTransform>().velocity.x = -5;
        break;
    case EInput::RIGHT:
        m_player->get<CTransform>().velocity.x = 5;
        break;
    default:
        break;
    }

    auto newPositionX = m_player->get<CTransform>().pos.x +
                        m_player->get<CTransform>().velocity.x;
    auto newPositionY = m_player->get<CTransform>().pos.y +
                        m_player->get<CTransform>().velocity.y;

    auto radius = m_player->get<CShape>().circle.getRadius();

    if (newPositionX + radius <= m_window.getSize().x &&
        newPositionX - radius >= 0) {
        m_player->get<CTransform>().pos.x = newPositionX;
    }
    if (newPositionY + radius <= m_window.getSize().y &&
        newPositionY - radius >= 0) {
        m_player->get<CTransform>().pos.y = newPositionY;
    }
}

void Game::sBulletMovement() {

    for (auto e : m_entityManager.getEntities("bullet")) {

        /*auto angle = e->get<CTransform>().angle;
        auto newPositionX = e->get<CTransform>().pos.x +
                            e->get<CTransform>().velocity.x * cos(angle);
        auto newPositionY = e->get<CTransform>().pos.y +
                            e->get<CTransform>().velocity.y * sin(angle);*/

        e->get<CTransform>().pos.x += e->get<CTransform>().velocity.x;
        e->get<CTransform>().pos.y += e->get<CTransform>().velocity.y;
    }
}

void Game::sEnemyMovement() {
    for (auto e : m_entityManager.getEntities("enemy")) {

        auto newPositionX =
            e->get<CTransform>().pos.x + e->get<CTransform>().velocity.x;
        auto newPositionY =
            e->get<CTransform>().pos.y + e->get<CTransform>().velocity.y;

        auto radius = e->get<CShape>().circle.getRadius();

        if (newPositionX + radius <= m_window.getSize().x &&
            newPositionX - radius >= 0) {
            e->get<CTransform>().pos.x = newPositionX;
        } else {
            e->get<CTransform>().velocity.x *= -1;
        }

        if (newPositionY + radius <= m_window.getSize().y &&
            newPositionY - radius >= 0) {
            e->get<CTransform>().pos.y = newPositionY;
        } else {
            e->get<CTransform>().velocity.y *= -1;
        }
    }
}

void Game::sUserInput() {

    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_running = false;
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->scancode) {
            case sf::Keyboard::Scancode::W:
                m_player->get<CInput>().currentInput = EInput::UP;
                break;

            case sf::Keyboard::Scancode::S:
                m_player->get<CInput>().currentInput = EInput::DOWN;
                break;

            case sf::Keyboard::Scancode::A:
                m_player->get<CInput>().currentInput = EInput::LEFT;
                break;
            case sf::Keyboard::Scancode::D:
                m_player->get<CInput>().currentInput = EInput::RIGHT;
                break;
            default:
                m_player->get<CInput>().currentInput = EInput::IDLE;
                break;
            }
        }

        if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            m_player->get<CInput>().currentInput = EInput::IDLE;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

            std::cout << "X: " << sf::Mouse::getPosition(m_window).x
                      << std::endl;
            std::cout << "Y: " << sf::Mouse::getPosition(m_window).y
                      << std::endl;

            // spawnBullet(m_player, Vec2(mouseWorldPos.x, mouseWorldPos.y));

            spawnBullet(m_player, Vec2(sf::Mouse::getPosition(m_window).x,
                                       sf::Mouse::getPosition(m_window).y));
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            // spawn special weapon here
        }
    }
}

void Game::sCollision() {
    // TODO: implement all proper collisions between getEntities
    // be sure to use the collision radius, NOT the shape radius
    //
    for (auto b : m_entityManager.getEntities("bullet")) {
        for (auto e : m_entityManager.getEntities("enemy")) {
            // calculate collosion
        }
    }
}

void Game::sEnemySpawner() {
    // TODO: use delay from config
    const auto delay = 180;

    if (m_currentFrame - m_lastEnemySpawnTime > delay) {
        spawnEnemy();
    }
}

/* void EntityManager::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);
    std::string first, last;
    int id;
    float avg;

    while (fin >> first >> last >> id >> avg) {
        std::cout << first << last << id << avg << std::endl;
    }
}*/
