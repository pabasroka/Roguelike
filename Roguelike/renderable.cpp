#include "renderable.hpp"

namespace component {
    Renderable::Renderable(std::shared_ptr<entity::Entity> parent_) :component::Component(parent_) {}
    sf::Sprite* Renderable::Render() {
        return nullptr;
    }
}
