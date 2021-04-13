#pragma once

#define EntityDefined

#ifndef ComponentDefined
    #include "Component.hpp"
#endif

#include "Position.hpp"
#include "EntityTags.hpp"
#include <vector>
#include <memory>

namespace entity {
    class EntitySystem;
    class Entity {
    public:
        Entity(utils::Position position_, entityTags tag_, const EntitySystem* scene_ = nullptr);
        entityTags tag;
        utils::Position position;
        const EntitySystem* scene;
        std::vector<std::unique_ptr<component::Component>> components;
        template <class T>
        T* GetComponent() {
            /*
             * Returns the first component of type T,
             * if no such component is found it returns nullptr
             */
            T* res = nullptr;
            for (unsigned int i = 0; i < components.size(); i++) {
                T* someComponent = dynamic_cast<T*>(components[i].get());
                if (someComponent != nullptr) {
                    res = someComponent;
                    break;
                }
            }
            return res;
        }
        virtual void Initialize(); // put specific component initialization here
    protected:
    private:
    };
}

#ifndef EntitySystemDefined
    #include "EntitySystem.hpp"
#endif
