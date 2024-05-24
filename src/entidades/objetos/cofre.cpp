#include "cofre.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include "../jugador.h"

using namespace godot;

void Cofre::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_open_area_body_entered", "body"), &Cofre::_on_open_area_body_entered);
    ClassDB::bind_method(D_METHOD("_on_animation_finished"), &Cofre::_on_animation_finished);
}

Cofre::Cofre() {
    animated_sprite = nullptr;
    open_area = nullptr;
    is_opened = false;
}

Cofre::~Cofre() {
    // Add your cleanup here.
}

void Cofre::_ready() {
    animated_sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    open_area = get_node<Area2D>("OpenArea");

    if (!animated_sprite) {
        UtilityFunctions::print("Error: AnimatedSprite2D node not found");
        return;
    }

    if (!open_area) {
        UtilityFunctions::print("Error: OpenArea node not found");
        return;
    }

    if (!open_area->is_connected("body_entered", Callable(this, "_on_open_area_body_entered"))) {
        open_area->connect("body_entered", Callable(this, "_on_open_area_body_entered"));
    }

    // Conectar la señal animation_finished
    if (!animated_sprite->is_connected("animation_finished", Callable(this, "_on_animation_finished"))) {
        animated_sprite->connect("animation_finished", Callable(this, "_on_animation_finished"));
    }
}

void Cofre::_on_open_area_body_entered(Node *body) {
    if (Object::cast_to<Player2D>(body)) {
        if (!is_opened && animated_sprite) {
            animated_sprite->play("open");
            is_opened = true;
        }
    }
}

void Cofre::_on_animation_finished() {
    if (animated_sprite && animated_sprite->is_playing() && animated_sprite->get_animation() == String("open")) {
        animated_sprite->play("opened");
    }
}
