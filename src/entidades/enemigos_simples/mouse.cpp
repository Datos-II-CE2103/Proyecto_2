#include "mouse.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>

using namespace godot;

void Raton::_bind_methods() {

    ClassDB::bind_method(D_METHOD("get_vidas"), &Raton::get_vidas);
    ClassDB::bind_method(D_METHOD("set_vidas", "p_vidas"), &Raton::set_vidas);
    ClassDB::add_property("Raton", PropertyInfo(Variant::INT, "vidas"), "set_vidas", "get_vidas");

    ClassDB::bind_method(D_METHOD("get_velocidad"), &Raton::get_velocidad);
    ClassDB::bind_method(D_METHOD("set_velocidad", "p_velocidad"), &Raton::set_velocidad);
    ClassDB::add_property("Raton", PropertyInfo(Variant::FLOAT, "velocidad"), "set_velocidad", "get_velocidad");

    ClassDB::bind_method(D_METHOD("_on_position_timer_timeout"), &Raton::_on_position_timer_timeout);
}

Raton::Raton() {

    vidas = 3;
    velocidad = 30.0;
    position_timer = nullptr;
    rng.seed(std::random_device()()); // Inicializar el motor de números aleatorios

    current_direction = Vector2(0, 0);
    last_horizontal_direction = Vector2(0, 0);

    animated_run = nullptr;
    animated_run_left = nullptr;

}
Raton::~Raton() {}

int Raton::get_vidas() const {
    return vidas;
}

void Raton::set_vidas(int p_vidas) {
    vidas = p_vidas;
}

double Raton::get_velocidad() const {
    return velocidad;
}

void Raton::set_velocidad(double p_velocidad) {
    velocidad = p_velocidad;
}

void Raton::_ready() {

    position_timer = get_node<Timer>("PositionTimer");

    if (!position_timer) {
        UtilityFunctions::print("Error: PositionTimer node not found");
        return;
    }

    if (!position_timer->is_connected("timeout", Callable(this, "_on_position_timer_timeout"))) {
        position_timer->connect("timeout", Callable(this, "_on_position_timer_timeout"));
    }

    choose_new_direction();

    animated_run = get_node<AnimatedSprite2D>("AnimatedRun");
    animated_run_left = get_node<AnimatedSprite2D>("AnimatedRun_Left");

    if (!animated_run || !animated_run_left) {
        UtilityFunctions::print("Error: One or more AnimatedSprite2D nodes not found");
        return;
    }

    animated_run->set_visible(true);
    animated_run->play("run_down");

    animated_run_left->set_visible(false);
}

void Raton::_process(double delta) {

    Vector2 velocity = current_direction * velocidad;
    set_velocity(velocity);
    move_and_slide();

    update_animations();
}

void Raton::_on_position_timer_timeout() {
    choose_new_direction();
}

void Raton::choose_new_direction() {
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

void Raton::update_animations() {

    if (current_direction == Vector2(0, 0)) {
        animated_run->set_visible(true);
        animated_run->play("run_down");
        animated_run_left->set_visible(false);
    } else if (current_direction.x > 0) {
        animated_run->set_visible(true);
        animated_run->play("run_right");
        animated_run_left->set_visible(false);
    } else if (current_direction.x < 0) {
        animated_run_left->set_visible(true);
        animated_run_left->play("run_left");
        animated_run->set_visible(false);
    } else if (current_direction.y < 0) {
        animated_run->set_visible(true);
        animated_run->play("run_down");
        animated_run_left->set_visible(false);
    } else if (current_direction.y > 0) {
        animated_run->set_visible(true);
        animated_run->play("run_up");
        animated_run_left->set_visible(false);
    }
}
