#include "EntitySystem.hpp"
#include "EntityTags.hpp"
#include "funcs.hpp"
#include "Entity.hpp"
#include <memory>
#include <pthread.h>
#include <vector>

namespace entity {
    EntitySystem::EntitySystem() {
        background = std::vector<std::shared_ptr<Entity>>();
        normal = std::vector<std::shared_ptr<Entity>>();
        top = std::vector<std::shared_ptr<Entity>>();
    }
    std::weak_ptr<Entity> EntitySystem::addEntity(Entity* entity, layers layer) {
        auto entityRef = std::shared_ptr<Entity>(entity);
        if (layer == layers::normal) normal.push_back(entityRef);
        elif (layer == layers::back) background.push_back(entityRef);
        else top.push_back(entityRef);
        return std::weak_ptr<Entity>(entityRef);
    }
    void EntitySystem::doUpdateTick() {
        for (unsigned long int i = 0; i < background.size(); i++) {
            auto entity = background[i];
            for (unsigned long int j = 0; j < entity->components.size(); j++) {
                entity->components[j]->Update();
            }
        }
        for (unsigned long int i = 0; i < normal.size(); i++) {
            auto entity = normal[i];
            for (unsigned long int j = 0; j < entity->components.size(); j++) {
                entity->components[j]->Update();
            }
        }
        for (unsigned long int i = 0; i < normal.size(); i++) {
            auto entity = normal[i];
            for (unsigned long int j = 0; j < entity->components.size(); j++) {
                entity->components[j]->Update();
            }
        }
    }
}
