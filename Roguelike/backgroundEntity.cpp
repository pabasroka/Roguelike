#include "backgroundEntity.hpp"
#include "EntitySystem.hpp"
#include "EntityTags.hpp"
#include "Position.hpp"
#include "funcs.hpp"
#include "shadedBackground.hpp"

namespace entity {
    background::background(const EntitySystem* scene_)
        : entity::Entity(utils::Position(), entityTags::visual, scene_) {
        Initialize();
    }
    void background::Initialize() {
        add_component(component::shadedBackground);
    }

    void background::LateInitialize() {}
}
