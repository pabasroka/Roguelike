#pragma once

#define add_component(name) components.push_back(std::unique_ptr<component::Component>( \
            dynamic_cast<component::Component*>( \
              new component::sprites::name( \
                  dynamic_cast<entity::Entity*>(this))))); 
