#ifndef GDEXTENSION_CPP_EXAMPLE_MOUSE_H
#define GDEXTENSION_CPP_EXAMPLE_MOUSE_H

#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/timer.hpp"
#include <random>

namespace godot {
    class Raton : public CharacterBody2D {
        GDCLASS(Raton, CharacterBody2D);

    private:

        int vidas;
        double velocidad;

        AnimatedSprite2D* animated_run;
        AnimatedSprite2D* animated_run_left;

        Vector2 current_direction;
        Vector2 last_horizontal_direction;

        Timer* position_timer;
        std::mt19937 rng; // Motor de números aleatorios

    protected:
        static void _bind_methods();

    public:
        Raton();
        ~Raton();

        int get_vidas() const;
        void set_vidas(int p_vidas);

        double get_velocidad() const;
        void set_velocidad(double p_velocidad);



        void _ready() override;
        void _process(double delta) override;
        void update_animations();

        void _on_position_timer_timeout();
        void choose_new_direction();

    };
}


#endif //GDEXTENSION_CPP_EXAMPLE_MOUSE_H
