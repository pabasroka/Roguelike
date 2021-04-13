#pragma once

#define EntityDefinied

#ifdef ComponentDefined
#else
#include "Component.hpp"
#endif
#include "Position.hpp"
#include <vector>
#include <memory>

namespace entity {
    class Entity {
    public:
        Entity(utils::Position position_);
        utils::Position position;
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
        } // returns pointer to component of type
        virtual void Initialize(); // put specific component initialization here
    protected:
    private:
    };
}
