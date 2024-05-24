#ifndef GDEXTENSION_CPP_EXAMPLE_MOUSE_H
#define GDEXTENSION_CPP_EXAMPLE_MOUSE_H

#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"

namespace godot {
    class Raton : public CharacterBody2D {
        GDCLASS(Raton, CharacterBody2D);

    private:

        int vidas;

        AnimatedSprite2D* animated_run;
        AnimatedSprite2D* animated_run_left;

        Vector2 current_direction;
        Vector2 last_horizontal_direction;

    protected:
        static void _bind_methods();

    public:
        Raton();
        ~Raton();

        void _ready() override;
        void _process(double delta) override;
        void update_animations();

    };
}


#endif //GDEXTENSION_CPP_EXAMPLE_MOUSE_H
