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

    Ref<PackedScene> resource;
    ResourceLoader *resource_loader = ResourceLoader::get_singleton();

    if (resource_loader) {
        resource = resource_loader->load("res://jugador.tscn");

        if (resource.is_valid()) {
            Player2D* player_node = Object::cast_to<Player2D>(resource->instantiate());
            if (player_node) {
                jugador=player_node;
                add_child(player_node);
            }
        } else {
            godot::UtilityFunctions::print("Error loading scene: res://jugador.tscn");
        }
    } else {
        godot::UtilityFunctions::print("Error: ResourceLoader singleton not found.");
    }

    jugador->set_vidas(45);


    

}

MainMapa::~MainMapa() {
    // Add your cleanup here.
}

void MainMapa::_process(double delta) {

}

