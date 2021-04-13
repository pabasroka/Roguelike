#include "Entity.hpp"
#include "Component.hpp"
#include <memory>
#include <typeinfo>


namespace entity {
    Entity::Entity(utils::Position position_) {
        position = position_;
        components = std::vector<std::unique_ptr<component::Component>>();
        Initialize();
    }
    /*
    template <class T>
    std::shared_ptr<T> Entity::GetComponent() {
      std::shared_ptr<T> res = nullptr;
      for (int i = 0; i < components.size(); i++) {
        std::shared_ptr<T> someComponent = std::dynamic_pointer_cast<T>(components[i]);
        if (someComponent != nullptr) {
          res = someComponent;
          break;
        }
      }
      return res;
    }
    */
    void Entity::Initialize() {}
}
