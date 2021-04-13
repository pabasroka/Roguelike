#pragma once
#include "sprite.hpp"

namespace component {
    namespace sprites {
        class korwin : public component::SpriteRenderer {
        public:
            korwin(entity::Entity* parent_);
            void Initialize();
        };
    }
}
