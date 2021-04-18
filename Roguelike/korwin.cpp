#include "korwin.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "funcs.hpp"

namespace component {
    namespace sprites {
        korwin::korwin(
            entity::Entity* parent_
        ) :component::ShadedSpriteRenderer(parent_) {
        }

        void korwin::Initialize() {
            assert(!texture.loadFromFile("resources/test.png"), "korwin failed to load texture");
            assert(!shader.loadFromFile(
                    "resources/shaders/testFrag.frag", 
                    sf::Shader::Fragment),
                "korwin failed to load shader");
            texture.setSmooth(true);
            sprite.setTexture(texture);
            sf::FloatRect spriteSize = sprite.getGlobalBounds();
            sprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
        }
    }
}
