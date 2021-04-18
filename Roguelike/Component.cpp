#include "Component.hpp"
#include "funcs.hpp"

namespace component {
    Component::Component(entity::Entity* parent_) {
        parent = parent_;
    }
    Component::~Component() {

    }
    void Component::Update() {}
    void Component::Awake() {}
}
