#include "Game.h"
#include "Components.hpp"
#include <SFML/Window/Mouse.hpp>
#include <memory>

Game::Game(const std::string &config) { init(config); }

void Game::init(const std::string &path) {
    // TODO read config fiel here,
    // use the premade PlayerConfig, EnemyConfig, BulletConfig Variables

    m_window.create(sf::VideoMode({1280, 720}), "Galaxy Wars");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

// some systems should function while paused(rendering)
// some systems should not (sMovement / input)
void Game::run() {
    m_entityManager.update();

    if (!m_paused) {
        // figure out which systems should go inside here and which not
    }

    sEnemySpawner();
    sMovement();
    sCollision();
    sUserInput();
    sRender();

    m_currentFrame++;
}

void Game::setPaused(bool paused) {
    // implement
}

void Game::spawnPlayer() {

    // TODO Finish adding all properties of the player with the correct values
    // from the config

    auto entity = m_entityManager.addEntity("player");

    entity->add<CTransform>(
        std::make_shared<CTransform>(Vec2(200.f, 200.f), Vec2(1.f, 1.f), 0.0f));

    entity->add<CShape>(std::make_shared<CShape>(32.f, 8, sf::Color(10, 10, 10),
                                                 sf::Color(255, 0, 0), 4.f));

    entity->add<CInput>(std::make_shared<CInput>());

    m_player = entity;
}

void Game::spawnEnemy() {
    auto entity = m_entityManager.addEntity("enemy");

    // TODO: get random position
    entity->add<CTransform>(
        std::make_shared<CTransform>(Vec2(200.f, 200.f), Vec2(1.f, 1.f), 0.0f));

    entity->add<CShape>(std::make_shared<CShape>(32.f, 8, sf::Color(10, 10, 10),
                                                 sf::Color(255, 0, 0), 4.f));

    entity->add<CInput>(std::make_shared<CInput>());

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
    auto bullet = m_entityManager.addEntity("bullet");

    bullet->add<CTransform>(
        std::make_shared<CTransform>(target, Vec2(0, 0), 0));
    bullet->add<CShape>(std::make_shared<CShape>(
        10, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2));
}

void Game::sRender() {
    m_window.clear();

    // m_player->cShape->circle.setPosition(m_player->cTransform->pos.x,
    // m_player->cTransform->pos.y);
    //
    // m_player->cTransform->angle += 1.0f;
    // m_player->cShape->circle.setRotation(m_player->cTransform->angle);

    // m_window.draw(m_player->cShape->circle);
    //
    for (auto e : m_entityManager.getEntities()) {

        // e->cShape->circle.setPosition(e->cTransform->pos.x,
        // e->cTransform->pos.y);
        //
        // e->cTransform->angle += 1.0f;
        // e->cShape->circle.setRotation(e->cTransform->angle);

        // m_window.draw(e->cShape->circle);
        // m_window.draw(e->cShape->circle);
    }

    m_window.display();
}

void Game::sMovement() {
    // TODO: implement all entity movement in this function
    // you should read the m_player->cInput component to determine if the player
    // is moving
    // implement Player movement
    //
    m_player->get<CTransform>().velocity = {0, 0};

    if (m_player->get<CInput>().up) {
        m_player->get<CTransform>().velocity.y = -5;
    }

    // sample movemnent speed update
    // m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    // m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::sUserInput() {

    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_running = false;
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->scancode) {
            case sf::Keyboard::Scancode::W:
                m_player->get<CInput>().up = true;
                break;

            case sf::Keyboard::Scancode::S:
                m_player->get<CInput>().down = true;
                break;

            case sf::Keyboard::Scancode::A:
                m_player->get<CInput>().left = true;
                break;
            case sf::Keyboard::Scancode::D:
                m_player->get<CInput>().right = true;
                break;
            default:
                break;
            }
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyReleased>()) {
            switch (keyPressed->scancode) {
            case sf::Keyboard::Scancode::W:
                m_player->get<CInput>().up = false;
                break;

            case sf::Keyboard::Scancode::S:
                m_player->get<CInput>().down = false;
                break;

            case sf::Keyboard::Scancode::A:
                m_player->get<CInput>().left = false;
                break;
            case sf::Keyboard::Scancode::D:
                m_player->get<CInput>().right = false;
                break;
            default:
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

            spawnBullet(m_player, Vec2(sf::Mouse::getPosition().x,
                                       sf::Mouse::getPosition().y));
            // event.mouseButton.x, event.mouseButton.y
            // call spawn bullet here
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
    // TODO: implement enemy spawning
    // use m_currentFrame - m_lastEnemySpawnTime to determine how long it has
    // been since the last enemy spawned
    //
    spawnEnemy();
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
