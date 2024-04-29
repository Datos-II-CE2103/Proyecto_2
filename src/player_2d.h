#ifndef PREELIMINAR_JUGADOR2D_H
#define PREELIMINAR_JUGADOR2D_H
#include "../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../godot-cpp/gen/include/godot_cpp/classes/camera2d.hpp"

namespace godot {

    /*! Clase Player2D para el uso del jugador
     * @extends CharacterBody2D
     */
    class Player2D : public CharacterBody2D {
        GDCLASS(Player2D, CharacterBody2D)

    private:
        double time_passed;

    protected:
        static void _bind_methods();

    public:
        Player2D();
        ~Player2D();

        void _process(double delta) override;
    };

}

#endif
