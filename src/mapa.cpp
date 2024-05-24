#include "mapa.h"
#include "entidades/jugador.h"
#include <godot_cpp/core/class_db.hpp>
#include "../../godot-cpp/gen/include/godot_cpp/classes/node2d.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/resource_loader.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/variant/utility_functions.hpp"

using namespace godot;


void MainMapa::_bind_methods() {
    }

MainMapa::MainMapa() {
    jugador= memnew(Player2D);
}

void MainMapa::_ready(){

}

MainMapa::~MainMapa() {
    // Add your cleanup here.
}

void MainMapa::_process(double delta) {

}

