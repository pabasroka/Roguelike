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

void gameloop() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml plswrk");
    window.setVerticalSyncEnabled(true);
    sf::View view(sf::Vector2f(100.f, 50.f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    window.setView(view);

    entity::EntitySystem testScene = entity::EntitySystem();
    testScene.addEntity(new entity::tests::korwintest(
	utils::Position(0, 0),
	&testScene
    ));


    while (window.isOpen()) {

	sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        window.clear();
	for (long unsigned int i = 0; i < testScene.background.size(); i++) {
	    print("drawing background item")
	    auto toRender = testScene.background[i]->GetComponent<component::Renderable>();
	    if (toRender != nullptr) {
		auto renderStruct = toRender->Render();
		if (renderStruct.sprite == nullptr) throw std::runtime_error("Nullptr in background render");
		if (renderStruct.shader == nullptr) window.draw(*(renderStruct.sprite));
		else window.draw(*(renderStruct.sprite), renderStruct.shader);
	    }
	}
	for (long unsigned int i = 0; i < testScene.normal.size(); i++) {
	    print("drawing normal item")
	    auto toRender = testScene.normal[i]->GetComponent<component::Renderable>();
	    if (toRender != nullptr) {
		auto renderStruct = toRender->Render();
		if (renderStruct.sprite == nullptr) throw std::runtime_error("Nullptr in background render");
		if (renderStruct.shader == nullptr) window.draw(*(renderStruct.sprite));
		else window.draw(*(renderStruct.sprite), renderStruct.shader);
	    }
	}
	for (long unsigned int i = 0; i < testScene.top.size(); i++) {
	    print("drawing top item")
	    auto toRender = testScene.top[i]->GetComponent<component::Renderable>();
	    if (toRender != nullptr) {
		auto renderStruct = toRender->Render();
		if (renderStruct.sprite == nullptr) throw std::runtime_error("Nullptr in background render");
		if (renderStruct.shader == nullptr) window.draw(*(renderStruct.sprite));
		else window.draw(*(renderStruct.sprite), renderStruct.shader);
	    }
	}
	print("drawing done")
        window.display();
    }
}
