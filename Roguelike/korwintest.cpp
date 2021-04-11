#include "korwin.hpp"
#include "funcs.hpp"
#include "korwintest.hpp"

namespace entity {
    namespace tests {      
            korwintest::korwintest(utils::Position position_) 
                : entity::Entity(position_) {
                Initialize();
            }
            void korwintest::Initialize() {
                add_component(korwin);
            }
    }
}
