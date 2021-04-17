#pragma once
#include <memory>

#define ComponentDefined

namespace entity {
    class Entity;
}

namespace component {
    class Component {
    public:
        Component(entity::Entity* parent_);
        virtual void Update(); // called every frame
        virtual void Awake(); // called on creation
        virtual ~Component();
    protected:
        entity::Entity* parent;
    };
}
#ifndef EntityDefined
    #include "Entity.hpp"
#endif
