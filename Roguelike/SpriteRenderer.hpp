#pragma once
#include "Renderable.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace component {
    class SpriteRenderer : public component::Renderable {
    public:
        SpriteRenderer(entity::Entity* parent_);
        void Awake();
        virtual void Initialize(); // set texture here
        renderStruct Render() override;
    protected:
        sf::Sprite sprite;
        sf::Texture texture;
    };
}
