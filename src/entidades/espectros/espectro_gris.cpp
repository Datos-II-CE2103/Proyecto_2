#include "espectro_gris.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

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
    rng.seed(std::random_device()()); // Inicializar el motor de números aleatorios

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

    choose_new_direction();
}

void EspectroGris::_process(double delta) {
    Vector2 velocity = current_direction * velocidad;
    set_velocity(velocity);
    move_and_slide();
    update_animations();
}

void EspectroGris::_on_position_timer_timeout() {
    choose_new_direction();
}

void EspectroGris::choose_new_direction() {
    std::uniform_int_distribution<int> dist(0, 3);
    int direction = dist(rng);

    switch (direction) {
        case 0:
            current_direction = Vector2(1, 0); // Derecha
            break;
        case 1:
            current_direction = Vector2(-1, 0); // Izquierda
            break;
        case 2:
            current_direction = Vector2(0, -1); // Arriba
            break;
        case 3:
            current_direction = Vector2(0, 1); // Abajo
            break;
    }
}

void EspectroGris::update_animations() {
    if (current_direction == Vector2(0, 0)) {
        animated_idle->set_visible(true);
        animated_idle->play("idle");
        animated_right->set_visible(false);
        animated_left->set_visible(false);
    } else if (current_direction == Vector2(1, 0)) {
        animated_idle->set_visible(false);
        animated_right->set_visible(true);
        animated_right->play("run_right");
        animated_left->set_visible(false);
    } else if (current_direction == Vector2(-1, 0)) {
        animated_idle->set_visible(false);
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
