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

    /*! Clase Player2D para el uso del jugador
     * @extends CharacterBody2D
     */
    class Player2D : public CharacterBody2D {
        GDCLASS(Player2D, CharacterBody2D)

    private:
        int vidas;
        double speed;
        int puntos;
        bool isAttacking;
        AnimatedSprite2D* player_animation;
        Timer* attack_timer;
        Area2D* attack_area;
        CollisionShape2D* attack_collision;
        Vector2 last_direction;

    protected:
        static void _bind_methods();

    public:
        Player2D();
        ~Player2D();

        void _physics_process(double delta);

        void _ready();

        void set_vidas(const int vidas);
        int get_vidas() const;

        void get_input();

        void update_animations();

        void _on_attack_timeout();
    };

}

#endif
