#include "EntitySystem.hpp"
#include <vector>

namespace entity {
    EntitySystem::EntitySystem(
        ) {
            background = std::vector<std::shared_ptr<Entity>>();
            normal = std::vector<std::shared_ptr<Entity>>();
            top = std::vector<std::shared_ptr<Entity>>();
    }
}
