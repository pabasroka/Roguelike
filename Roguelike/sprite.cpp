#include "sprite.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


namespace component {
    SpriteRenderer::SpriteRenderer(std::shared_ptr<entity::Entity> parent_) : component::Renderable(parent_) {}
    void SpriteRenderer::Awake() {
        Initialize();
    }
    sf::Sprite* SpriteRenderer::Render(std::shared_ptr<utils::Position> cameraPos) {

        sprite.setPosition(parent->position.xy - cameraPos->xy);
        std::cout << "drawing at " << (parent->position.xy - cameraPos->xy).x;
        std::cout << " " << (parent->position.xy - cameraPos->xy).y << std::endl;
        // todo some culling
        return &sprite;
    }
    void SpriteRenderer::Initialize() {}
}
