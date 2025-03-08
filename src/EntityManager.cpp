#include "./Entity.hpp"
#include <fstream>
#include <map>

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager {
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    std::map<std::string, EntityVec> m_entityMap;
    size_t m_totalEntities = 0;

    void removeDeadEntities(EntityVec &vec) {}

public:
    EntityManager() = default;
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    EntityVec &getEntities();
    EntityVec &getEntities(const std::string &tag);

    void update() {
        // add entities from m_entitiesToAdd
        // add them to the vector of all entities
        // add them tot he vector inside the map, with the tag as a key

        removeDeadEntities(m_entities);

        for (auto &[tag, entityVec] : m_entityMap) {
            removeDeadEntities(entityVec);
        }
    }

    void loadFromFile(const std::string &filename);

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
/* void EntityManager::loadFromFile(const std::string &filename) {
    std::ifstream fin(filename);
    std::string first, last;
    int id;
    float avg;

    while (fin >> first >> last >> id >> avg) {
        std::cout << first << last << id << avg << std::endl;
    }
}*/
