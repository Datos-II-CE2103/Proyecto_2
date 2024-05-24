#ifndef GDEXTENSION_CPP_EXAMPLE_OJOESPECTRAL_H
#define GDEXTENSION_CPP_EXAMPLE_OJOESPECTRAL_H

#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"

namespace godot {
    class OjoEspectral : public CharacterBody2D {
        GDCLASS(OjoEspectral, CharacterBody2D);

    private:


    protected:
        static void _bind_methods();

    public:
        OjoEspectral();

        ~OjoEspectral();

        /*void _ready() override;

        void _process(double delta) override;*/

    };
}


#endif
