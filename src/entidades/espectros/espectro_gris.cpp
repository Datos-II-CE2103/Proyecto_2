#include "espectro_gris.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void EspectroGris::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_vidas"), &EspectroGris::get_vidas);
    ClassDB::bind_method(D_METHOD("set_vidas", "p_vidas"), &EspectroGris::set_vidas);
    ClassDB::add_property("EspectroGris", PropertyInfo(Variant::INT, "vidas"), "set_vidas", "get_vidas");

    ClassDB::bind_method(D_METHOD("get_velocidad"), &EspectroGris::get_velocidad);
    ClassDB::bind_method(D_METHOD("set_velocidad", "p_velocidad"), &EspectroGris::set_velocidad);
    ClassDB::add_property("EspectroGris", PropertyInfo(Variant::FLOAT, "velocidad"), "set_velocidad", "get_velocidad");

    ClassDB::bind_method(D_METHOD("_on_position_timer_timeout"), &EspectroGris::_on_position_timer_timeout);
}

EspectroGris::EspectroGris() {
    vidas = 5;
    velocidad = 30.0;
    position_timer = nullptr;
    current_direction = Vector2(0, 0);
    last_horizontal_direction = Vector2(0, 0);
    current_patrol_point_index = 0;

    animated_idle = nullptr;
    animated_right = nullptr;
    animated_left = nullptr;
}

EspectroGris::~EspectroGris() {
    // Add your cleanup here.
}

int EspectroGris::get_vidas() const {
    return vidas;
}

void EspectroGris::set_vidas(int p_vidas) {
    vidas = p_vidas;
}

double EspectroGris::get_velocidad() const {
    return velocidad;
}

void EspectroGris::set_velocidad(double p_velocidad) {
    velocidad = p_velocidad;
}

void EspectroGris::_ready() {
    position_timer = get_node<Timer>("PositionTimer");

    if (!position_timer) {
        UtilityFunctions::print("Error: PositionTimer node not found");
        return;
    }

    if (!position_timer->is_connected("timeout", Callable(this, "_on_position_timer_timeout"))) {
        position_timer->connect("timeout", Callable(this, "_on_position_timer_timeout"));
    }

    animated_idle = get_node<AnimatedSprite2D>("AnimatedIdle");
    animated_right = get_node<AnimatedSprite2D>("AnimatedRight");
    animated_left = get_node<AnimatedSprite2D>("AnimatedLeft");

    if (!animated_idle || !animated_right || !animated_left) {
        UtilityFunctions::print("Error: One or more AnimatedSprite2D nodes not found");
        return;
    }

    animated_idle->play("idle");
    animated_right->set_visible(false);
    animated_left->set_visible(false);

    // Define los puntos de patrullaje en forma de cuadrado
    patrol_points.push_back(Vector2(0, 0));
    patrol_points.push_back(Vector2(100, 0));
    patrol_points.push_back(Vector2(100, 100));
    patrol_points.push_back(Vector2(0, 100));

    move_to_next_patrol_point();

    // Obtener referencias a las áreas y los collision shapes
    area_down = get_node<Area2D>("AreaRange_Down");
    area_right = get_node<Area2D>("AreaRange_Right");
    area_left = get_node<Area2D>("AreaRange_Left");
    area_up = get_node<Area2D>("AreaRange_Up");

    collision_down = area_down->get_node<CollisionShape2D>("CollisionRange_Down");
    collision_right = area_right->get_node<CollisionShape2D>("CollisionRange_Right");
    collision_left = area_left->get_node<CollisionShape2D>("CollisionRange_Left");
    collision_up = area_up->get_node<CollisionShape2D>("CollisionRange_Up");

    // Desactivar todas las áreas y los collision shapes al inicio
    area_down->set_collision_layer_value(1, false);
    area_right->set_collision_layer_value(1, false);
    area_left->set_collision_layer_value(1, false);
    area_up->set_collision_layer_value(1, false);
}

void EspectroGris::_process(double delta) {
    Vector2 velocity = current_direction * velocidad;
    set_velocity(velocity);
    move_and_slide();
    update_animations();

    if (get_global_position().distance_to(patrol_points[current_patrol_point_index]) < 10) {
        move_to_next_patrol_point();
    }

    if (current_direction == Vector2(0, -1)) {

        area_down->set_collision_layer_value(1, false);
        area_right->set_collision_layer_value(1, false);
        area_left->set_collision_layer_value(1, false);

        area_up->set_collision_layer_value(1, true);
        collision_up->set_disabled(false);
    } else if (current_direction == Vector2(1, 0)) {

        area_down->set_collision_layer_value(1, false);
        area_left->set_collision_layer_value(1, false);
        area_up->set_collision_layer_value(1, false);

        area_right->set_collision_layer_value(1, true);
        collision_right->set_disabled(false);
    } else if (current_direction == Vector2(-1, 0)) {
        area_down->set_collision_layer_value(1, false);
        area_right->set_collision_layer_value(1, false);
        area_up->set_collision_layer_value(1, false);

        area_left->set_collision_layer_value(1, true);
        collision_left->set_disabled(false);
    } else if (current_direction == Vector2(0, 1)) {

        area_right->set_collision_layer_value(1, false);
        area_left->set_collision_layer_value(1, false);
        area_up->set_collision_layer_value(1, false);

        area_down->set_collision_layer_value(1, true);
        collision_down->set_disabled(false);
    }
}

void EspectroGris::_on_position_timer_timeout() {
    move_to_next_patrol_point();
}

void EspectroGris::move_to_next_patrol_point() {
    current_patrol_point_index = (current_patrol_point_index + 1) % patrol_points.size();
    Vector2 target = patrol_points[current_patrol_point_index];
    current_direction = (target - get_global_position()).normalized();

    // Actualiza la última dirección horizontal
    if (current_direction.x != 0) {
        last_horizontal_direction = current_direction;
    }
}

void EspectroGris::update_animations() {
    if (current_direction == Vector2(0, 0)) {
        animated_idle->set_visible(true);
        animated_idle->play("idle");
        animated_right->set_visible(false);
        animated_left->set_visible(false);
    } else if (current_direction.x > 0) {
        animated_idle->set_visible(false);
        animated_right->set_visible(true);
        animated_right->play("run_right");
        animated_left->set_visible(false);
    } else if (current_direction.x < 0) {
        animated_idle->set_visible(false);
        animated_right->set_visible(false);
        animated_left->set_visible(true);
        animated_left->play("run_left");
    } else {
        animated_idle->set_visible(false);
        if (last_horizontal_direction.x > 0) {
            animated_right->set_visible(true);
            animated_right->play("run_right");
            animated_left->set_visible(false);
        } else if (last_horizontal_direction.x < 0) {
            animated_right->set_visible(false);
            animated_left->set_visible(true);
            animated_left->play("run_left");
        } else {
            animated_idle->set_visible(true);
            animated_idle->play("idle");
            animated_right->set_visible(false);
            animated_left->set_visible(false);
        }
    }
}
