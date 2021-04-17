#include "korwin.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <stdexcept>
#include <iostream>

namespace component {
    namespace sprites {
        korwin::korwin(
	    entity::Entity* parent_
	) :component::ShadedSpriteRenderer(parent_) {
            Initialize();
        }
        void korwin::Initialize() {
            if (!texture.loadFromFile("resources/test.png")) {
                throw std::runtime_error("korwin failed to load texture");
            }
	    if (!shader.loadFromFile(
		"resources/shaders/testFrag.frag", 
		sf::Shader::Fragment)) {
		throw std::runtime_error("korwin failed to load shader");
	    }	
            texture.setSmooth(true);
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
            sprite.setTexture(texture);
            std::cout << "loaded korWIN" << std::endl;
        }
    }
}
