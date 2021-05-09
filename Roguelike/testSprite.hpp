#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "sprite.hpp"

namespace component {
    namespace sprites {
        class testSprite : public component::SpriteRenderer {
        public:
            testSprite(entity::Entity* parent_);
            void Initialize();
        };
    }
}
