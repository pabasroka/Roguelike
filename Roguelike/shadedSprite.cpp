#include "shadedSprite.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "renderable.hpp"
#include <SFML/Graphics/Shader.hpp>

namespace component {
    ShadedSpriteRenderer::ShadedSpriteRenderer(
	entity::Entity* parent_
    ) : component::SpriteRenderer(parent_) {
	renderCount = 0;
    }
    void ShadedSpriteRenderer::Awake() {
	Initialize();
    }
    renderStruct ShadedSpriteRenderer::Render() {
	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shader.setUniform("renderCount", renderCount);
	renderCount += 0.1;
	return {&sprite, &shader};
    }

}
