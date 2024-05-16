#include "jugador.h"

#include <godot_cpp/core/class_db.hpp>

#include "../../godot-cpp/gen/include/godot_cpp/classes/resource_loader.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/variant/utility_functions.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/packed_scene.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/input.hpp"
#include "../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"



using namespace godot;


void Player2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_vidas"), &Player2D::get_vidas);
    ClassDB::bind_method(D_METHOD("set_vidas", "p_vidas"), &Player2D::set_vidas);
    ClassDB::add_property("Player2D", PropertyInfo(Variant::INT, "vidas"), "set_vidas", "get_vidas");

}

Player2D::Player2D() {
    // Initialize any variables here.
    vidas=5;
    puntos=0;
    speed=40;
}

Player2D::~Player2D() {
    // Add your cleanup here.
}
void Player2D::set_vidas(const int p_vidas) {
    vidas=p_vidas;
}
int Player2D::get_vidas() const {
    return vidas;
}
/*
void Player2D::_ready() {
    Ref<PackedScene> resource;
    ResourceLoader *resource_loader = ResourceLoader::get_singleton();


    if (resource_loader) {
        resource = resource_loader->load("res://animtacionJugador.tscn");

        if (resource.is_valid()) {
            AnimatedSprite2D* animated_sprite = Object::cast_to<AnimatedSprite2D>(resource->instantiate());
            player_animation=animated_sprite;
            if (animated_sprite) {
                add_child(animated_sprite);
        }
        } else {
            godot::UtilityFunctions::print("Error loading scene: res://scene.tscn");
        }
    } else {
        godot::UtilityFunctions::print("Error: ResourceLoader singleton not found.");
    }
}*/

void Player2D::update_animations() {
    Vector2 veloc = get_velocity();
    if (veloc.x > 0) {
        //player_animation->play("derecha");
        //UtilityFunctions::print(veloc);
    } else if (veloc.x < 0) {
        //player_animation->play("izquierda");
        //UtilityFunctions::print(veloc);
    } else if (veloc.y < 0) {
        //player_animation->play("arriba");
        //UtilityFunctions::print(veloc);
    } else if (veloc.y > 0) {
        //player_animation->play("abajo");
        //UtilityFunctions::print(veloc);
    } else {
        //player_animation->stop();
    }
}

void Player2D::get_input() {
    Vector2 input_direction = Input::get_singleton()->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
    Vector2 veloc = input_direction * speed;
    set_velocity(veloc);
    move_and_slide();
}

void Player2D::_physics_process(double delta) {
    Player2D::get_input();
    update_animations();
}

/*
void Player2D::_process(double delta) {
    Player2D::_physics_process(delta);

}*/
