#include "korwin.hpp"
#include "funcs.hpp"
#include "korwintest.hpp"

namespace entity {
    namespace tests {      
            korwintest::korwintest(utils::Position position_, const EntitySystem* scene_) 
                : entity::Entity(position_, entityTags::enemy, scene) {
                Initialize();
            }
            void korwintest::Initialize() {
                add_component(component::sprites::korwin);
            }
    }
}
