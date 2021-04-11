#pragma once
#include "sprite.hpp"

namespace component {
    namespace sprites {
        class korwin : public component::SpriteRenderer {
        public:
            korwin(std::shared_ptr<entity::Entity> parent_);
            void Initialize();
        };
    }
}
