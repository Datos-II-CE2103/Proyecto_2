#include "jugador.h"

#include <godot_cpp/core/class_db.hpp>

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
    velocidad=1;
}

Player2D::~Player2D() {
    // Add your cleanup here.
}

void Player2D::_process(double delta) {
    double time_passed=0;
    time_passed+= delta;

    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

    set_position(new_position);
}

void Player2D::set_vidas(const int p_vidas) {
    vidas=p_vidas;
}
int Player2D::get_vidas() const {
    return vidas;
}