#pragma once

#define add_component(name) components.push_back(std::unique_ptr<component::Component>( \
            dynamic_cast<component::Component*>( \
              new component::sprites::name( \
                  dynamic_cast<entity::Entity*>(this))))); 

#include <iostream>

#define print(var) std::cout << var << std::endl;

#define elif else if
