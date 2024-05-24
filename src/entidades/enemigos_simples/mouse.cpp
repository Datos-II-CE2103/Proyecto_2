#include "mouse.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Raton::_bind_methods() {}

Raton::Raton() {

    vidas=5;

    current_direction = Vector2(0, 0);
    last_horizontal_direction = Vector2(0, 0);

    animated_run = nullptr;
    animated_run_left = nullptr;
}

Raton::~Raton() {}

void Raton::_ready() {

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

    update_animations();
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

