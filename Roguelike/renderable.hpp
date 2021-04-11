#pragma once

#include "Component.hpp"
#include "Position.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace component {
    class Renderable : public component::Component {
    public:
        Renderable(std::shared_ptr<entity::Entity> parent_);
        virtual sf::Sprite* Render();
    };
}
