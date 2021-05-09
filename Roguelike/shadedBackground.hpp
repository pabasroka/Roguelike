#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include "renderable.hpp"

namespace component {
    class shadedBackground : public component::Renderable {
    public:
        shadedBackground(entity::Entity* parent_);
        virtual void initialize();
        void Awake() override;
        void setView(sf::Window* window);
        renderStruct Render() override;
    protected:
        sf::Shader shader;
    private:
        sf::RectangleShape renderTarget;
        sf::RenderWindow* windowref = nullptr;
        sf::Vector2f lastSize;
    };
}
