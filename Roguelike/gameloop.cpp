#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <stdexcept>
#include <chrono>
#include "Component.hpp"
#include "Entity.hpp"
#include "EntitySystem.hpp"
#include "EntityTags.hpp"
#include "Position.hpp"
#include "korwin.hpp"
#include "korwintest.hpp"
#include "renderable.hpp"
#include "constants.hpp"
#include "funcs.hpp"
#include "player.hpp"
#include "backgroundEntity.hpp"
#include "shadedBackground.hpp"
#include "testEntity.hpp"

void gameloop() {
    // Setup clock for measuring frametimes
    auto lastTime = std::chrono::steady_clock::now();
    // ========================== GAME WINDOW ========================== 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml plswrk");
    sf::View view;
    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setCenter(100.f, 100.f);
    
    window.setVerticalSyncEnabled(true);

    entity::EntitySystem testScene = entity::EntitySystem();
    // setup background
    testScene.addEntity(new entity::background(
        &testScene
    ), entity::layers::back).lock()->GetComponent<component::shadedBackground>()->setView(&window);
    // add test dev entity
    testScene.addEntity(new entity::testEntity(
        utils::Position(600, 600),
        &testScene
    ));
    // add 2x korwin
    testScene.addEntity(new entity::tests::korwintest(
        utils::Position(300, 0),
        &testScene
    ));
    testScene.addEntity(new entity::tests::korwintest(
        utils::Position(0, 0),
        &testScene
    ));
    // add player entity
    testScene.addEntity(new entity::playerEntity(
        utils::Position(1, 1),
        &testScene
    ));
    
    // get refrance to player
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
                print("Window size changed!")
            }
        }
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> timeSinceLastFrame = now - lastTime;
        // print fps
        print(1.0 / timeSinceLastFrame.count());
        lastTime = now;
        double normalFpsDeviation = (1./60.) / timeSinceLastFrame.count();

        // Simple movement mechanics
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.lock()->position.xy -= sf::Vector2f(-5 / normalFpsDeviation, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.lock()->position.xy += sf::Vector2f(-5 / normalFpsDeviation, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.lock()->position.xy -= sf::Vector2f(0, 5.f / normalFpsDeviation);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.lock()->position.xy += sf::Vector2f(0, 5.f / normalFpsDeviation);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            view.rotate(15.f / normalFpsDeviation);

        // Refresh view
        view.setCenter(player.lock()->position.xy);
        window.setView(view);
        // do Update() tick;
        testScene.doUpdateTick();
        testScene.doFixedUpdateTick(timeSinceLastFrame.count());

        // DRAWING SECTION
        window.clear();
        for (long unsigned int i = 0; i < testScene.background.size(); i++) {
            auto toRender = testScene.background[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assert(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.normal.size(); i++) {
            auto toRender = testScene.normal[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assert(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.top.size(); i++) {
            auto toRender = testScene.top[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assert(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        window.display();
    }
}
