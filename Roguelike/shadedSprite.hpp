#pragma once 
#include "Component.hpp"
#include "Entity.hpp"
#include "sprite.hpp"
#include <SFML/Graphics/Shader.hpp>

namespace component {
    class ShadedSpriteRenderer : public component::SpriteRenderer {
    public:
        ShadedSpriteRenderer(entity::Entity* parent_);
        void Awake() override;
        renderStruct Render() override;
    protected:
        sf::Shader shader;
    };
}
