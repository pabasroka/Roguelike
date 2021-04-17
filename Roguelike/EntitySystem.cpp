#include "EntitySystem.hpp"
#include "funcs.hpp"
#include "Entity.hpp"
#include <memory>
#include <vector>

namespace entity {
    EntitySystem::EntitySystem() {
            background = std::vector<std::shared_ptr<Entity>>();
            normal = std::vector<std::shared_ptr<Entity>>();
            top = std::vector<std::shared_ptr<Entity>>();
    }
    std::weak_ptr<Entity> EntitySystem::addEntity(Entity* entity, layers layer) {
	print("Adding Entity to normal")
	auto entityRef = std::shared_ptr<Entity>(entity);
	if (layer == layers::normal) normal.push_back(entityRef);
	elif (layer == layers::back) background.push_back(entityRef);
	else top.push_back(entityRef);
	return std::weak_ptr<Entity>(entityRef);
    }
}
