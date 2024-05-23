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
    ClassDB::bind_method(D_METHOD("_on_attack_timeout"), &Player2D::_on_attack_timeout);
}

Player2D::Player2D() {
    vidas = 5;
    puntos = 0;
    speed = 40;
    player_animation = nullptr;
    attack_timer = nullptr;
    attack_area = nullptr;
    attack_collision = nullptr;
    isAttacking = false;
    last_direction = Vector2(0, 1);
}

Player2D::~Player2D() {
    // Add your cleanup here.
}

void Player2D::set_vidas(const int p_vidas) {
    vidas = p_vidas;
}

int Player2D::get_vidas() const {
    return vidas;
}

void Player2D::_ready() {
    player_animation = get_node<AnimatedSprite2D>("CollisionShape2D/AnimatedSprite2D");
    attack_timer = get_node<Timer>("AttackTimer");
    attack_area = get_node<Area2D>("AttackArea");
    attack_collision = attack_area->get_node<CollisionShape2D>("AttackCollision");

    if (!player_animation) {
        UtilityFunctions::print("Error: AnimatedSprite2D node not found");
        return;
    }

    if (!attack_timer) {
        UtilityFunctions::print("Error: AttackTimer node not found");
        return;
    }

    if (!attack_area) {
        UtilityFunctions::print("Error: AttackArea node not found");
        return;
    }

    if (!attack_collision) {
        UtilityFunctions::print("Error: AttackCollision node not found");
        return;
    }

    if (!attack_timer->is_connected("timeout", Callable(this, "_on_attack_timeout"))) {
        attack_timer->connect("timeout", Callable(this, "_on_attack_timeout"));
    }

    attack_collision->set_disabled(true);
}

void Player2D::update_animations() {
    Vector2 veloc = get_velocity();

    if (isAttacking) {
        if (last_direction == Vector2(0, 1)) {
            player_animation->play("attack_down");
        } else if (last_direction == Vector2(0, -1)) {
            player_animation->play("attack_up");
        } else if (last_direction == Vector2(1, 0)) {
            player_animation->play("attack_right");
        } else if (last_direction == Vector2(-1, 0)) {
            player_animation->play("attack_left");
        }
    } else if (veloc.x > 0) {
        player_animation->play("run_right");
        last_direction = Vector2(1, 0);
    } else if (veloc.x < 0) {
        player_animation->play("run_left");
        last_direction = Vector2(-1, 0);
    } else if (veloc.y < 0) {
        player_animation->play("run_up");
        last_direction = Vector2(0, -1);
    } else if (veloc.y > 0) {
        player_animation->play("run_down");
        last_direction = Vector2(0, 1);
    } else {
        if (last_direction == Vector2(0, 1)) {
            player_animation->play("idle_down");
        } else if (last_direction == Vector2(0, -1)) {
            player_animation->play("idle_up");
        } else if (last_direction == Vector2(1, 0)) {
            player_animation->play("idle_right");
        } else if (last_direction == Vector2(-1, 0)) {
            player_animation->play("idle_left");
        }
    }
}

void Player2D::get_input() {
    if (!isAttacking) {
        Vector2 input_direction = Input::get_singleton()->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
        Vector2 veloc = input_direction * speed;
        set_velocity(veloc);
    }

    if (Input::get_singleton()->is_action_just_pressed("ui_select") && !isAttacking) {
        isAttacking = true;
        attack_timer->start();
        attack_collision->set_disabled(false);
    }

    if (!isAttacking) {
        move_and_slide();
    }
}

void Player2D::_on_attack_timeout() {
    isAttacking = false;
    attack_collision->set_disabled(true);
}

void Player2D::_physics_process(double delta) {
    get_input();
    update_animations();
}
