#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <box2d/b2_math.h>
#include <stdexcept>
#include <chrono>
#include "Component.hpp"
#include "Entity.hpp"
#include "Entity-System.hpp"
#include "Entity-Tags.hpp"
#include "Utils-Position.hpp"
#include "Component-Korwin.hpp"
#include "Entity-Korwin.hpp"
#include "Component-Renderable.hpp"
#include "constants.hpp"
#include "funcs.hpp"
#include "Entity-Player.hpp"
#include "Entity-Background.hpp"
#include "Component-Shaded-Background.hpp"
#include "Entity-Test.hpp"
#include "Component-Physics.hpp"

#define playerSpeed .1

void gameloop() {
    // Setup clock for measuring frametimes
    auto lastTime = std::chrono::steady_clock::now();
    // ========================== GAME WINDOW ========================== 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml plswrk");
    sf::View view;
    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setCenter(100.f, 100.f);
    window.setVerticalSyncEnabled(true);
    
    // create scene
    entity::EntitySystem testScene = entity::EntitySystem();
    // setup background
    testScene.addEntity(new entity::background(
        &testScene
    ), entity::layers::back).lock()->GetComponent<component::shadedBackground>()->setView(&window);
    // add test dev entity
    testScene.addEntity(new entity::testEntity(
        utils::Position(0, 600),
        &testScene
    ));
    // add 2x korwin
    auto thatKoriwn = testScene.addEntity(new entity::tests::korwintest(
        utils::Position(6, 0),
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
    
    // get refrence to player
    auto player = testScene.GetEntityByTag(entity::entityTags::player);

    // ========================== GAME LOOP ========================== 
    while (window.isOpen()) {
        // EVENTS
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            if (event.type == sf::Event::EventType::Resized) {
                // handle changed window size
                auto windowSize = window.getSize();
                view.setSize((float) windowSize.x, (float) windowSize.y);
                print("Window size changed!");
                printVec2(windowSize);
            }
        }
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> timeSinceLastFrame = now - lastTime;
        lastTime = now;
        // print fps
        std::cout << "fps: " << 1.0 / timeSinceLastFrame.count() << "\r"; 
        std::cout.flush();

        // not-so-simple movement mechanics
        b2Vec2 playerForce {0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            playerForce.x += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            playerForce.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            playerForce.y -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            playerForce.y += 1;

        // if player wants movement, give him movement
        if (playerForce.Length() > 0) {
            // get refrence to PhysicsBody component
            auto playerPhys = player.lock()->GetComponent<component::PhysicsBody>();
            playerForce.Normalize();
            playerForce.x *= playerSpeed;
            playerForce.y *= playerSpeed;
            playerPhys->body->ApplyForceToCenter(playerForce, true);
        }
        auto preUpdatePos = player.lock()->position;
        // do Update() tick;
        testScene.doUpdateTick();
        testScene.doFixedUpdateTick(timeSinceLastFrame.count());

        // Refresh view
        auto postUpdatePos = player.lock()->position;
        sf::Vector2f newViewPos = (-preUpdatePos.xy + postUpdatePos.xy) * float(25.0) + postUpdatePos.xy;
        view.setCenter(newViewPos);
        window.setView(view);

        // DRAWING SECTION
        window.clear();
        for (long unsigned int i = 0; i < testScene.background.size(); i++) {
            auto toRender = testScene.background[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assertCond(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.normal.size(); i++) {
            auto toRender = testScene.normal[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assertCond(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.top.size(); i++) {
            auto toRender = testScene.top[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assertCond(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        window.display();
    }
}
