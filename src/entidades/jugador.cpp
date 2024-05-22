#include "jugador.h"

#include <godot_cpp/core/class_db.hpp>

#include "../../godot-cpp/gen/include/godot_cpp/classes/resource_loader.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/variant/utility_functions.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/packed_scene.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/input.hpp"
#include "../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../godot-cpp/gen/include/godot_cpp/classes/tile_map.hpp"



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
    player_animation= memnew(AnimatedSprite2D);
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

void Player2D::_ready() {

    AnimatedSprite2D* temp_animations = get_node<AnimatedSprite2D>("CollisionShape2D/AnimatedSprite2D");

    if (temp_animations){
        player_animation=temp_animations;
    }
}

void Player2D::update_animations() {
    Vector2 veloc = get_velocity();

    if (veloc.x==0 & veloc.y==0){
        player_animation->play("idle_down");
    }
    if (veloc.x > 0) {
        player_animation->play("run_right");
        //UtilityFunctions::print(veloc);
    } else if (veloc.x < 0) {
        player_animation->play("run_left");
        //UtilityFunctions::print(veloc);
    } else if (veloc.y < 0) {
        player_animation->play("run_up");
        //UtilityFunctions::print(veloc);
    } else if (veloc.y > 0) {
        player_animation->play("run_down");
        //UtilityFunctions::print(veloc);
    } else {
        player_animation->stop();
    }
}

void Player2D::get_input() {
    Vector2 input_direction = Input::get_singleton()->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
    Vector2 veloc = input_direction * speed;
    set_velocity(veloc);
    move_and_slide();

    /*TileMap* temp_tilemap= get_node<TileMap>("../../TileMap");

    if (temp_tilemap){
        Vector2 tempActual=temp_tilemap->local_to_map(get_global_position());
        if ((tempActual != tileActual)){
            tileActual=tempActual;
            UtilityFunctions::print(tileActual);
        }

    }*/
}

void Player2D::_physics_process(double delta) {
    Player2D::get_input();
    update_animations();
}


