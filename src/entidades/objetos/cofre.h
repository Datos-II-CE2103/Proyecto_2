#ifndef GDEXTENSION_CPP_EXAMPLE_COFRE_H
#define GDEXTENSION_CPP_EXAMPLE_COFRE_H

#include "../../../godot-cpp/gen/include/godot_cpp/classes/static_body2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/area2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/collision_shape2d.hpp"
#include "entidades/jugador.h"

namespace godot {
    class Cofre : public StaticBody2D {
        GDCLASS(Cofre, StaticBody2D);

    private:
        AnimatedSprite2D *animated_sprite;
        Area2D *open_area;
        bool is_opened;

    protected:
        static void _bind_methods();

    public:
        Cofre();
        ~Cofre();

        void _ready() override;

        void _on_open_area_body_entered(Node *body);
        void _on_animation_finished();
    };
}

#endif //GDEXTENSION_CPP_EXAMPLE_COFRE_H
