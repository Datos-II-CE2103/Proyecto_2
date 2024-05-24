#ifndef PREELIMINAR_JUGADOR2D_H
#define PREELIMINAR_JUGADOR2D_H

#include "../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/camera2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"
#include "../../godot-cpp/include/godot_cpp/variant/vector2.hpp"
#include "../../godot-cpp/include/godot_cpp/core/object.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/timer.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/area2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/collision_shape2d.hpp"

namespace godot {

    class Player2D : public CharacterBody2D {
        GDCLASS(Player2D, CharacterBody2D)

    private:
        int vidas;
        double speed;
        int puntos;
        bool isAttacking;

        AnimatedSprite2D* player_animation;
        Vector2 last_direction;
        Timer* attack_timer;

        Area2D* attack_area_right;
        Area2D* attack_area_left;
        Area2D* attack_area_up;
        Area2D* attack_area_down;
        CollisionShape2D* attack_collision_right;
        CollisionShape2D* attack_collision_left;
        CollisionShape2D* attack_collision_up;
        CollisionShape2D* attack_collision_down;

    protected:
        static void _bind_methods();

    public:
        Player2D();
        ~Player2D();

        void _ready();
        void _physics_process(double delta);
        void get_input();
        void update_animations();
        void _on_attack_timeout();
        void set_vidas(const int vidas);
        int get_vidas() const;

        // Nueva función para emitir la señal
        void emit_position_changed();
        // Señal para la posición cambiada
        void position_changed(Vector2 new_position);
    };
}

#endif
