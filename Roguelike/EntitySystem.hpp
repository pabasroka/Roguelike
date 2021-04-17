#pragma once

#include "EntityTags.hpp"
#define EntitySystemDefined
#ifndef EntityDefined
    #include "Entity.hpp"
#endif
#include <memory>
#include <vector>

namespace entity {
    enum layers {
	back,
	normal,
	top
    };
    class EntitySystem {
        public:
            std::vector<std::shared_ptr<Entity>> background;
            std::vector<std::shared_ptr<Entity>> normal;
            std::vector<std::shared_ptr<Entity>> top;
            EntitySystem();
            std::weak_ptr<Entity> GetEntityByTag(entityTags tag);
            // returns first entity in normal with tag
            std::vector<std::weak_ptr<Entity>> GetEntitiesByTag(entityTags tag);
            // returns all entities in normal with tag
	    void doUpdateTick();
	    std::weak_ptr<Entity> addEntity(Entity* entity, layers layer = layers::normal);
	    // Add entity to scene
	    // use with new operator 
    };
}
