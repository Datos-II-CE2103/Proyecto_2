#ifndef GDEXTENSION_CPP_EXAMPLE_OJOESPECTRAL_H
#define GDEXTENSION_CPP_EXAMPLE_OJOESPECTRAL_H

#include "../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/camera2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"
#include "../../godot-cpp/include/godot_cpp/variant/vector2.hpp"
#include "../../godot-cpp/include/godot_cpp/core/object.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/timer.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/area2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/collision_shape2d.hpp"

namespace godot {
    class Player2D;

    class OjoEspectral : public CharacterBody2D {
        GDCLASS(OjoEspectral, CharacterBody2D);

    private:
        AnimatedSprite2D* ojo_animation;
        Area2D* range_area;
        CollisionShape2D* range_collision;

    protected:
        static void _bind_methods();

    public:
        OjoEspectral();
        ~OjoEspectral();

        void update_animations();
        void _ready() override;
        void _process(double delta) override;
        void _on_range_area_body_entered(Node* body);
        void body_entered_range_area(Node* body);
    };
}

#endif // GDEXTENSION_CPP_EXAMPLE_OJOESPECTRAL_H
