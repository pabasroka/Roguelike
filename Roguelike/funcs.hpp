#pragma once

#include <stdexcept>
#include <iostream>
#define add_component(name) components.push_back(std::unique_ptr<component::Component>( \
            dynamic_cast<component::Component*>( \
              new name( \
                  dynamic_cast<entity::Entity*>(this))))); 


#define print(var) std::cerr << __FILE__ << ":" << __LINE__ << "\t" << #var << " -> \t" << var << std::endl;

#define assert(condition, msg) if(condition) { \
    std::cerr << "ASSERTION: " << __FILE__ << ":" << __LINE__ << "\t->\t" << #condition << std::endl; \
    throw std::runtime_error(msg); \
}

#define elif else if

