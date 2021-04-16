#pragma once
#include "Component.hpp"
#include "Entity.hpp"
#include "Position.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>

struct actionStruct {
	sf::Sprite* sprite;
	sf::Shape* shape;
};

namespace component {
	class Action : public component::Component {
	public:
		Action(entity::Entity* parent_);
		virtual actionStruct Move(sf::Vector2f movePos) = 0;
	};
}


