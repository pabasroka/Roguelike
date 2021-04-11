#pragma once
#include <memory>

#define ComponentDefined

namespace entity {
    class Entity;
}

namespace component {
    class Component {
    public:
        Component(std::shared_ptr<entity::Entity> parent_);
        virtual void Update(); // called every frame
        virtual void Awake(); // called on creation
        virtual ~Component();
    protected:
        std::shared_ptr<entity::Entity> parent;
    };
}
#ifdef EntityDefinied
#else
#include "Entity.hpp"
#endif
