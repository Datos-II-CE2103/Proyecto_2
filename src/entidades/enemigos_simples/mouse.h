#ifndef GDEXTENSION_CPP_EXAMPLE_MOUSE_H
#define GDEXTENSION_CPP_EXAMPLE_MOUSE_H

#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"

namespace godot {
    class Raton : public CharacterBody2D {
        GDCLASS(Raton, CharacterBody2D);

    private:

        int vidas;

    protected:
        static void _bind_methods();

    public:
        Raton();

        ~Raton();

        /*void _ready() override;

        void _process(double delta) override;*/

    };
}


#endif //GDEXTENSION_CPP_EXAMPLE_MOUSE_H
