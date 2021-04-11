#include "Component.hpp"

namespace component {
    Component::Component(std::shared_ptr<entity::Entity> parent_) {
        parent = parent_;
    }
    Component::~Component() {

    }
    void Component::Update() {}
    void Component::Awake() {}
}
