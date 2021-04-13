#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <stdexcept>
#include "korwin.hpp"
#include "korwintest.hpp"
#include "renderable.hpp"
#include "constants.hpp"

void gameloop() {

    // ========================== GAME WINDOW ========================== 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml plswrk");
    sf::View view;
    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setCenter(100.f, 100.f);

    int viewCounter{};
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    entity::tests::korwintest test(utils::Position(100, 100));
    auto korwinRenderer = test.GetComponent<component::Renderable>();

    sf::RectangleShape s(sf::Vector2f(50.f, 50.f));


    // ========================== GAME LOOP ========================== 
    while (window.isOpen()) {

        // EVENTS
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // Simple movement mechanics
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            s.move(sf::Vector2f(5, 0.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            s.move(sf::Vector2f(-5, 0.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            s.move(sf::Vector2f(0, -5.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            s.move(sf::Vector2f(0, 5.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            view.rotate(15.f);

        if (viewCounter >= 15) {
            viewCounter = 0;
            view.move(sf::Vector2f(-5.f, 0.f));
        }
        else {
            viewCounter++;
        }
 
        // Refresh view
        window.setView(view);

        // DRAWING SECTION
        window.clear();
        renderStruct toRender = korwinRenderer->Render();
        if (toRender.sprite == nullptr) throw std::runtime_error("nullptr on sprite!");
        if (toRender.shader == nullptr) {
            window.draw(*(toRender.sprite));
        }
        window.draw(s);
        //window.draw(*(korwinRenderer->Render()));

        window.display();
    }
}
