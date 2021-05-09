#pragma once 

#include "Entity.hpp"
#include "EntitySystem.hpp"
#include "Position.hpp"

namespace entity {
    class background : public Entity {
    public:
        background(const EntitySystem* scene_ = nullptr);
        void Initialize();
    };
}
