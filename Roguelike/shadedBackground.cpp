#include "shadedBackground.hpp"
#include "Entity.hpp"
#include "renderable.hpp"
#include "funcs.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

namespace component {
    shadedBackground::shadedBackground(entity::Entity* parent_) : Renderable(parent_) {
        renderTarget = sf::RectangleShape();
        windowref = nullptr;
    }
    void shadedBackground::Awake() {
        initialize();
    }

    void shadedBackground::initialize() {
        assert(!shader.loadFromFile(
            "resources/shaders/background.frag",
            sf::Shader::Fragment
        ), "failed to load background shader");
    }
    void shadedBackground::setView(sf::Window* window) {
        windowref = dynamic_cast<sf::RenderWindow*>(window);
    }
    renderStruct shadedBackground::Render() {
        assert(windowref == nullptr, "windowref is not set!");
        auto windowSize = sf::Vector2f(windowref->getSize());
        renderTarget.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
        renderTarget.setSize(windowSize);
        renderTarget.setPosition(windowref->mapPixelToCoords(sf::Vector2i(
            0, 0
        )));
        auto position = windowref->getView().getCenter();

        shader.setUniform("pos", sf::Vector2f(position.x - windowSize.x / 2,  position.y - windowSize.y / 2));
        shader.setUniform("size", windowSize);
        return renderStruct {&renderTarget, &shader};
    }
}
