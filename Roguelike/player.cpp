#include "player.hpp"
#include "Component.hpp"
#include "EntitySystem.hpp"
#include "EntityTags.hpp"
#include "Position.hpp"
#include "funcs.hpp"
#include "physicsBody.hpp"
#include "playerSprite.hpp"
#include <box2d/b2_math.h>

namespace entity {
    playerEntity::playerEntity(utils::Position position_, const EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::player, scene_) {
        Initialize();
    }

    void playerEntity::Initialize() {
        add_component(component::sprites::player);
        add_component(component::PhysicsBody);
    }
    
    void playerEntity::LateInitialize() {
        component::PhysicsBody* physics = GetComponent<component::PhysicsBody>();
        assertCond(physics == nullptr, "no physics body");
        physics->body->SetLinearDamping(2);
    }
}
