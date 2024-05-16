#ifndef PREELIMINAR_JUGADOR2D_H
#define PREELIMINAR_JUGADOR2D_H
#include "../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/camera2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"
#include "../../godot-cpp/include/godot_cpp/variant/vector2.hpp"
#include "../../godot-cpp/include/godot_cpp/core/object.hpp"

namespace godot {

    /*! Clase Player2D para el uso del jugador
     * @extends CharacterBody2D
     */
    class Player2D : public CharacterBody2D {
        GDCLASS(Player2D, CharacterBody2D)

    private:
        int vidas;
        double speed;
        Vector2 velocity;
        //breadcruming
        int puntos;



    protected:
        static void _bind_methods();

    public:
        Player2D();
        ~Player2D();

        //void _process(double delta) override;
        void _physics_process(double delta);

        void _ready();

        void set_vidas(const int vidas);
        int get_vidas() const;

        void get_input();

        void update_animations();



    };


}

#endif
