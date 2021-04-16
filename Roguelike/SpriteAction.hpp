#pragma once
#include "Action.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace component {
	class SpriteAction : public component::Action {
	public:
		SpriteAction(entity::Entity* parent_);

		// Sprite moving mechanics
		actionStruct Move(sf::Vector2f movePos) override;
	protected:
		sf::Sprite sprite;
	};
}


