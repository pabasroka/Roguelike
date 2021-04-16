#include "SpriteAction.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

namespace component {
	SpriteAction::SpriteAction(entity::Entity* parent_) : component::Action(parent_) {}

	// Sprite moving mechanics
	actionStruct SpriteAction::Move(sf::Vector2f movePos) {
		// move
		//sf::Sprite::move(movePos.x, movePos.y);
		return actionStruct{ &sprite, nullptr };
	}
}