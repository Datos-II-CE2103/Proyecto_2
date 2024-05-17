//
// Created by alexander on 17/05/24.
//

#ifndef GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H
#define GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H

#include "../enemigos.h"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"


namespace godot {

    /*! Clase Player2D para el uso del jugador
     * @extends CharacterBody2D
     */
    class EspectroGris : public CharacterBody2D,EnemigoB {
        GDCLASS(EspectroGris, CharacterBody2D)

    private:
        int maxpd;

    protected:
        static void _bind_methods();

    public:
        EspectroGris();
        ~EspectroGris();

        //void _process(double delta) override;



        //void _ready();
    };


}




#endif //GDEXTENSION_CPP_EXAMPLE_ESPECTRO_GRIS_H
