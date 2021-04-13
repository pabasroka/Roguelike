#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "Position.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct renderStruct {
    sf::Sprite* sprite;
    sf::Shader* shader;
};

namespace component {
    class Renderable : public component::Component {
    public:
        Renderable(entity::Entity* parent_);
        virtual renderStruct Render() = 0;
    };
}
