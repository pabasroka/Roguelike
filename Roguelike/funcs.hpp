#pragma once

#define add_component(name) components.push_back(std::shared_ptr<component::Component>( \
            dynamic_cast<component::Component*>( \
              new component::sprites::name( \
                std::shared_ptr<entity::Entity>( \
                  dynamic_cast<entity::Entity*>(this)))))); 
