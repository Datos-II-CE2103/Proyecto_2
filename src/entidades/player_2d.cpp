#include "player_2d.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void Player2D::_bind_methods() {
}

Player2D::Player2D() {
    // Initialize any variables here.
    time_passed = 0.0;
}

Player2D::~Player2D() {
    // Add your cleanup here.
}

void Player2D::_process(double delta) {
    time_passed += delta;

    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

    set_position(new_position);
}