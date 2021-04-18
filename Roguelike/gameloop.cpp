#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <stdexcept>
#include "Component.hpp"
#include "Entity.hpp"
#include "EntityTags.hpp"
#include "Position.hpp"
#include "korwin.hpp"
#include "korwintest.hpp"
#include "renderable.hpp"
#include "constants.hpp"
#include "funcs.hpp"
#include "player.hpp"

void gameloop() {
    // ========================== GAME WINDOW ========================== 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml plswrk");
    sf::View view;
    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setCenter(100.f, 100.f);

    window.setVerticalSyncEnabled(true);


    entity::EntitySystem testScene = entity::EntitySystem();
    testScene.addEntity(new entity::tests::korwintest(
        utils::Position(300, 0),
        &testScene
    ));
    testScene.addEntity(new entity::tests::korwintest(
        utils::Position(0, 0),
        &testScene
    ));
    testScene.addEntity(new entity::playerEntity(
        utils::Position(1, 1),
        &testScene
    )); 

    // print number of enemies: should be 2
    print(testScene.GetEntitiesByTag(entity::entityTags::enemy).size());
    print(testScene.GetEntitiesByTag(entity::entityTags::player).size());
    auto player = testScene.GetEntityByTag(entity::entityTags::player);

    // ========================== GAME LOOP ========================== 
    while (window.isOpen()) {

        // EVENTS
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            if (event.type == sf::Event::EventType::Resized) {
                auto windowSize = window.getSize();
                view.setSize((float) windowSize.x, (float) windowSize.y);
            }
        }

        // Simple movement mechanics
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.lock()->position.xy -= sf::Vector2f(-5, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.lock()->position.xy += sf::Vector2f(-5, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.lock()->position.xy -= sf::Vector2f(0, 5.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.lock()->position.xy += sf::Vector2f(0, 5.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            view.rotate(15.f);

        // Refresh view
        view.setCenter(player.lock()->position.xy);
        window.setView(view);


        // do Update() tick;
        testScene.doUpdateTick();

        // DRAWING SECTION
        window.clear();
        for (long unsigned int i = 0; i < testScene.background.size(); i++) {
            auto toRender = testScene.background[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assert(renderStruct.sprite == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.sprite));
                else window.draw(*(renderStruct.sprite), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.normal.size(); i++) {
            auto toRender = testScene.normal[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assert(renderStruct.sprite == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.sprite));
                else window.draw(*(renderStruct.sprite), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.top.size(); i++) {
            auto toRender = testScene.top[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assert(renderStruct.sprite == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.sprite));
                else window.draw(*(renderStruct.sprite), renderStruct.shader);
            }
        }
        window.display();
    }
}
