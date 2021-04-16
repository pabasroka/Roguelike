#include "SpriteRenderer.hpp"
#include "renderable.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


namespace component {
    SpriteRenderer::SpriteRenderer(entity::Entity* parent_) : component::Renderable(parent_) {}
    void SpriteRenderer::Awake() {
        Initialize();
    }
    renderStruct SpriteRenderer::Render() {
        return renderStruct {&sprite, nullptr};
    }
    void SpriteRenderer::Initialize() {}
}
