//
// Created by alexander on 4/05/24.
//

#ifndef GDEXTENSION_CPP_EXAMPLE_MAPA_H
#define GDEXTENSION_CPP_EXAMPLE_MAPA_H

#include "../../godot-cpp/gen/include/godot_cpp/classes/node2d.hpp"
#include "entidades/jugador.h"
#include "../../godot-cpp/gen/include/godot_cpp/classes/packed_scene.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/node.hpp"

namespace godot {

    /*! Clase Player2D para el uso del jugador
     * @extends CharacterBody2D
     */
    class MainMapa : public Node2D {
        GDCLASS(MainMapa, Node2D)

    private:
        Player2D* jugador;
        PackedScene jugadorTSCN;


    protected:
        static void _bind_methods();

    public:
        MainMapa();
        ~MainMapa();

        void _ready();

        void _process(double delta) override;

        template<typename T>
        static T *cast_to(Object *p_object);
    };


}


#endif //GDEXTENSION_CPP_EXAMPLE_MAPA_H
