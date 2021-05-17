#include "Entity-System.hpp"
#include "Entity-Tags.hpp"
#include "funcs.hpp"
#include "Entity.hpp"
#include "Component-Physics.hpp"
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <memory>
#include <pthread.h>
#include <vector>

namespace entity {
    EntitySystem::EntitySystem() {
        background = std::vector<std::shared_ptr<Entity>>();
        normal = std::vector<std::shared_ptr<Entity>>();
        top = std::vector<std::shared_ptr<Entity>>();
        physicsWorld = std::shared_ptr<b2World>(new b2World(b2Vec2(0., 0.))); 
    }
    std::weak_ptr<Entity> EntitySystem::addEntity(Entity* entity, layers layer) {
        auto entityRef = std::shared_ptr<Entity>(entity);
        auto physics = entityRef->GetComponent<component::PhysicsBody>();
        if (physics != nullptr) {
            physics->world = physicsWorld;
        }
        for (unsigned long int i = 0; i < entityRef->components.size(); i++) {
            entityRef->components[i]->Awake();
        }
        entityRef->LateInitialize();
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
        for (unsigned long int i = 0; i < top.size(); i++) {
            auto entity = top[i];
            for (unsigned long int j = 0; j < entity->components.size(); j++) {
                entity->components[j]->Update();
            }
        }
    }
    void EntitySystem::doFixedUpdateTick(double timeDelta) {
        for (unsigned long int i = 0; i < background.size(); i++) {
            auto entity = background[i];
            for (unsigned long int j = 0; j < entity->components.size(); j++) {
                entity->components[j]->FixedUpdate(timeDelta);
            }
        }
        for (unsigned long int i = 0; i < normal.size(); i++) {
            auto entity = normal[i];
            for (unsigned long int j = 0; j < entity->components.size(); j++) {
                entity->components[j]->FixedUpdate(timeDelta);
            }
        }
        for (unsigned long int i = 0; i < top.size(); i++) {
            auto entity = top[i];
            for (unsigned long int j = 0; j < entity->components.size(); j++) {
                entity->components[j]->FixedUpdate(timeDelta);
            }
        }
        // do physics stuff
        physicsWorld->Step(timeDelta, 8, 3);
    }
    std::weak_ptr<Entity> EntitySystem::GetEntityByTag(entityTags tag) {
        std::weak_ptr<Entity> res = std::weak_ptr<Entity>(std::shared_ptr<Entity>(nullptr));
        for (unsigned long int i = 0; i < normal.size(); i++) {
            if (normal[i]->tag == tag){
                res = std::weak_ptr<Entity>(normal[i]);
                break;
            }
        }
        return res;
    }

    std::vector<std::weak_ptr<Entity>> EntitySystem::GetEntitiesByTag(entityTags tag) {
        auto resultVec = std::vector<std::weak_ptr<Entity>>();
        for (unsigned long int i = 0; i < normal.size(); i++) {
            if (normal[i]->tag == tag){
                resultVec.push_back(normal[i]);
            }
        }
        return resultVec;
    }
    EntitySystem::~EntitySystem() {}
}
