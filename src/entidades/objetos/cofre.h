#ifndef GDEXTENSION_CPP_EXAMPLE_COFRE_H
#define GDEXTENSION_CPP_EXAMPLE_COFRE_H

#include "../../../godot-cpp/gen/include/godot_cpp/classes/static_body2d.hpp"

namespace godot{
    class Cofre : public StaticBody2D {
        GDCLASS(Cofre, StaticBody2D);

    protected:
        static void _bind_methods();

    public:
        Cofre();
        ~Cofre();

        /*void _ready() override;
        void _process(double delta) override;*/

        //void update_animations();
    };
}

#endif //GDEXTENSION_CPP_EXAMPLE_COFRE_H
