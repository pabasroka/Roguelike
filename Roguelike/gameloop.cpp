#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <stdexcept>
#include "Entity.hpp"
#include "korwin.hpp"
#include "korwintest.hpp"
#include "renderable.hpp"
#include "constants.hpp"
#include "funcs.hpp"

void gameloop() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml plswrk");
    window.setVerticalSyncEnabled(true);
    sf::View view(sf::Vector2f(100.f, 50.f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    window.setView(view);

    entity::EntitySystem testScene = entity::EntitySystem();

    add_Entity_normal(testScene, entity::tests::korwintest(utils::Position(100, 100)));

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        window.clear();
        renderStruct toRender = korwinRenderer->Render();
        if (toRender.sprite == nullptr) throw std::runtime_error("nullptr on sprite!");
        if (toRender.shader == nullptr) {
            window.draw(*(toRender.sprite));
        }

        window.display();
    }
}
