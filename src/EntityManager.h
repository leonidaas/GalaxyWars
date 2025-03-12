#pragma once

#include "Entity.hpp"
#include <map>

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager {
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    std::map<std::string, EntityVec> m_entityMap;
    size_t m_totalEntities = 0;

public:
    EntityManager() = default;
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    EntityVec &getEntities();
    EntityVec &getEntities(const std::string &tag);

    void removeDeadEntities(EntityVec &vec);

    void update();

    // when iterating over a vector / list
    // for(auto& a : vec) -> best practice because otherwise the content would
    // be copied
    //
    // const std::vector<Student>& getStudents() const { const in the beginning
    // means that the result can not be changed, const at the end means, it wont
    // change the input
    //  return m_students
    // }
};
