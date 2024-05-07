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
    jugador= nullptr;
}

void MainMapa::_ready(){

    Ref<PackedScene> scene;
    ResourceLoader *resource_loader = ResourceLoader::get_singleton();

    if (resource_loader) {
        scene = resource_loader->load("res://jugador.tscn");

        if (scene.is_valid()) {
            Node *instantiated_scene = scene->instantiate();
            this->add_child(instantiated_scene);
            Node *instantiated_scene2 = scene->instantiate();
            this->add_child(instantiated_scene2);
        } else {
            godot::UtilityFunctions::print("Error loading scene: res://scene.tscn");
        }
    } else {
        godot::UtilityFunctions::print("Error: ResourceLoader singleton not found.");
    }

    Player2D* p2p = memnew(Player2D);


    // Set the text of the label.

    p2p->set_vidas(45);


    // Add the label as a child of this node.

    add_child(p2p);

    child->set_vidas(60);

    //continue here (need to fix get_node is not working)
    

}

MainMapa::~MainMapa() {
    // Add your cleanup here.
}

void MainMapa::_process(double delta) {

}

