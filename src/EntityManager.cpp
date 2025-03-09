#include "EntityManager.h"
#include "./Entity.hpp"
#include <map>

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {

    // you can't use "make_shared" here because Entity is a private/friend class
    // and therefor you need to create it with the new keyword but it still has
    // the same functionality
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_entitiesToAdd.push_back(entity);

    return entity;
}

EntityVec &EntityManager::getEntities() { return m_entities; }
EntityVec &EntityManager::getEntities(const std::string &tag) {
    return m_entityMap[tag];
}

void EntityManager::removeDeadEntities(EntityVec &vec) {

    m_entities.erase(
        std::remove_if(vec.begin(), vec.end(),
                       [](const auto &e) { return !e->isActive(); }),
        m_entities.end());
}

void EntityManager::update() {

    for (auto e : m_entitiesToAdd) {
        m_entities.push_back(e);

        m_entityMap[e->tag()].push_back(e);
    }

    m_entitiesToAdd.clear(); // remove them as they are added to m_entities

    removeDeadEntities(m_entities);

    for (auto &[tag, entityVec] : m_entityMap) {
        removeDeadEntities(entityVec);
    }
}
