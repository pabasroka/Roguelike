#include "player.hpp"
#include "EntitySystem.hpp"
#include "EntityTags.hpp"
#include "Position.hpp"
#include "funcs.hpp"
#include "playerSprite.hpp"

namespace entity {
    playerEntity::playerEntity(utils::Position position_, const EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::player, scene_) {
        Initialize();
    }

    void playerEntity::Initialize() {
        add_component(component::sprites::player);
    }

}
