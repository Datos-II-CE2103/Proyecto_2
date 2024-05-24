#ifndef GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H
#define GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H

#include "../enemigos.h"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/timer.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/area2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/collision_shape2d.hpp"
#include <vector>

namespace godot {

    class EspectroGris : public CharacterBody2D, EnemigoB {
        GDCLASS(EspectroGris, CharacterBody2D)

    private:
        int vidas;
        double velocidad;
        Timer *position_timer;
        Vector2 current_direction;
        Vector2 last_horizontal_direction;
        std::vector<Vector2> patrol_points;
        int current_patrol_point_index;

        bool detected;

        AnimatedSprite2D *animated_idle;
        AnimatedSprite2D *animated_right;
        AnimatedSprite2D *animated_left;

        Area2D* area_down;
        Area2D* area_right;
        Area2D* area_left;
        Area2D* area_up;

        CollisionShape2D* collision_down;
        CollisionShape2D* collision_right;
        CollisionShape2D* collision_left;
        CollisionShape2D* collision_up;

    protected:
        static void _bind_methods();

    public:
        EspectroGris();
        ~EspectroGris();

        int get_vidas() const;
        void set_vidas(int p_vidas);

        double get_velocidad() const;
        void set_velocidad(double p_velocidad);

        void _ready() override;
        void _process(double delta) override;

        void _on_position_timer_timeout();
        void move_to_next_patrol_point();
        void update_animations();

        void _on_body_entered_range_area(Node* body);
    };

}

#endif //GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H
