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
    ClassDB::bind_method(D_METHOD("emit_position_changed"), &Player2D::emit_position_changed);
    ADD_SIGNAL(MethodInfo("position_changed", PropertyInfo(Variant::VECTOR2, "new_position")));
}

Player2D::Player2D() {
    vidas = 5;
    puntos = 0;
    speed = 40;
    player_animation = nullptr;
    attack_timer = nullptr;
    attack_area_right = nullptr;
    attack_area_left = nullptr;
    attack_area_up = nullptr;
    attack_area_down = nullptr;
    attack_collision_right = nullptr;
    attack_collision_left = nullptr;
    attack_collision_up = nullptr;
    attack_collision_down = nullptr;
    isAttacking = false;
    last_direction = Vector2(0, 1);
    globaltilemap = memnew(TileMap);
    breadcrumbing = new DoublyLinkedList();
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

    globaltilemap = get_node<TileMap>("../TileMap");
    player_animation = get_node<AnimatedSprite2D>("PlayerSprite2D");
    attack_timer = get_node<Timer>("AttackTimer");
    attack_area_right = get_node<Area2D>("AttackAreaRight");
    attack_area_left = get_node<Area2D>("AttackAreaLeft");
    attack_area_up = get_node<Area2D>("AttackAreaUp");
    attack_area_down = get_node<Area2D>("AttackAreaDown");
    attack_collision_right = attack_area_right->get_node<CollisionShape2D>("AttackCollisionRight");
    attack_collision_left = attack_area_left->get_node<CollisionShape2D>("AttackCollisionLeft");
    attack_collision_up = attack_area_up->get_node<CollisionShape2D>("AttackCollisionUp");
    attack_collision_down = attack_area_down->get_node<CollisionShape2D>("AttackCollisionDown");

    if (!player_animation) {
        UtilityFunctions::print("Error: AnimatedSprite2D node not found");
        return;
    }

    if (!attack_timer) {
        UtilityFunctions::print("Error: AttackTimer node not found");
        return;
    }

    if (!attack_area_right || !attack_area_left || !attack_area_up || !attack_area_down) {
        UtilityFunctions::print("Error: AttackArea node not found");
        return;
    }

    if (!attack_collision_right || !attack_collision_left || !attack_collision_up || !attack_collision_down) {
        UtilityFunctions::print("Error: AttackCollision node not found");
        return;
    }

    if (!attack_timer->is_connected("timeout", Callable(this, "_on_attack_timeout"))) {
        attack_timer->connect("timeout", Callable(this, "_on_attack_timeout"));
    }

    attack_collision_right->set_disabled(true);
    attack_collision_left->set_disabled(true);
    attack_collision_up->set_disabled(true);
    attack_collision_down->set_disabled(true);
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

        // Desactivar todas las colisiones de ataque
        attack_collision_right->set_disabled(true);
        attack_collision_left->set_disabled(true);
        attack_collision_up->set_disabled(true);
        attack_collision_down->set_disabled(true);

        // Activar la colisión de ataque según la última dirección
        if (last_direction == Vector2(0, 1)) {
            attack_collision_down->set_disabled(false);
        } else if (last_direction == Vector2(0, -1)) {
            attack_collision_up->set_disabled(false);
        } else if (last_direction == Vector2(1, 0)) {
            attack_collision_right->set_disabled(false);
        } else if (last_direction == Vector2(-1, 0)) {
            attack_collision_left->set_disabled(false);
        }
    }

    if (!isAttacking) {
        move_and_slide();
    }

    if (globaltilemap){
        Vector2 tempActual=globaltilemap->local_to_map(get_global_position());
        if ((tempActual != tileActual)){
            tileActual=tempActual;
            breadcrumbing->insertLast(tileActual);
            //UtilityFunctions::print(tileActual);
        }

    }
}

void Player2D::_on_attack_timeout() {
    isAttacking = false;
    // Desactivar todas las colisiones de ataque
    attack_collision_right->set_disabled(true);
    attack_collision_left->set_disabled(true);
    attack_collision_up->set_disabled(true);
    attack_collision_down->set_disabled(true);
}

void Player2D::emit_position_changed() {
    emit_signal("position_changed", get_position());
}

void Player2D::_physics_process(double delta) {
    Vector2 old_position = get_position();
    get_input();
    update_animations();
    if (old_position != get_position()) {
        emit_position_changed();
    }
}