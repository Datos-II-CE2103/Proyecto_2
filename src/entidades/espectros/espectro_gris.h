#ifndef GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H
#define GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H

#include "../enemigos.h"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/timer.hpp"
#include <random>

namespace godot {

    class EspectroGris : public CharacterBody2D, EnemigoB {
        GDCLASS(EspectroGris, CharacterBody2D)

    private:
        int vidas;
        double velocidad;
        Timer *position_timer;
        Vector2 current_direction;
        std::mt19937 rng; // Motor de números aleatorios

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
        void choose_new_direction();
    };

}

#endif //GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H
