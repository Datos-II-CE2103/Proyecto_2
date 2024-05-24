#include "chocobo.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "entidades/jugador.h"
#include <godot_cpp/classes/animated_sprite2d.hpp>

using namespace godot;

void Chocobo::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_player_position_changed", "new_position"), &Chocobo::_on_player_position_changed);
}

Chocobo::Chocobo() {
    vidas = 5;

    current_direction = Vector2(0, 0);
    last_horizontal_direction = Vector2(0, 0);

    animated_run_right = nullptr;
    animated_run_left = nullptr;
}

Chocobo::~Chocobo() {}

void Chocobo::_ready() {

    animated_run_right = get_node<AnimatedSprite2D>("AnimatedRunRight");
    animated_run_left = get_node<AnimatedSprite2D>("AnimatedRunLeft");

    if (!animated_run_right || !animated_run_left) {
        UtilityFunctions::print("Error: One or more AnimatedSprite2D nodes not found");
        return;
    }

    animated_run_right->set_visible(true);
    animated_run_right->play("run_right");

    animated_run_left->set_visible(false);

}

void Chocobo::_process(double delta) {
    update_animations();

    // Calcula la dirección hacia la posición del jugador
    Vector2 direction = player_position - get_position();

    // Normaliza la dirección para mantener una velocidad constante
    if (direction.length() > 0) {
        direction = direction.normalized();
    }

    current_direction = direction;

    set_velocity(current_direction * 10);
    move_and_slide();
}

void Chocobo::update_animations() {
    if (current_direction == Vector2(0, 0)) {
        animated_run_right->set_visible(true);
        animated_run_right->play("run_right");
        animated_run_left->set_visible(false);
    } else if (current_direction.x > 0) {
        animated_run_right->set_visible(true);
        animated_run_right->play("run_right");
        animated_run_left->set_visible(false);
    } else if (current_direction.x < 0) {
        animated_run_left->set_visible(true);
        animated_run_left->play("run_left");
        animated_run_right->set_visible(false);
    } else {
        if (last_horizontal_direction.x > 0) {
            animated_run_right->set_visible(true);
            animated_run_right->play("run_right");
            animated_run_left->set_visible(false);
        } else if (last_horizontal_direction.x < 0) {
            animated_run_left->set_visible(true);
            animated_run_left->play("run_left");
            animated_run_right->set_visible(false);
        } else {
            animated_run_right->set_visible(true);
            animated_run_right->play("run_right");
            animated_run_left->set_visible(false);

        }
    }
}


void Chocobo::_on_player_position_changed(Vector2 new_position) {

    player_position = new_position;
}

bool Chocobo::check_line_of_sight(Vector2 target_position) {
    /* Implementa Bresenham Line of Sight
     Retorna true si hay línea de visión, de lo contrario retorna false
     Verificar si hay obstáculos entre el chocobo y el jugador
     Usar RayCast2D para verificar si hay obstáculos en el camino
     Si no hay obstáculos, retornar true; de lo contrario, retornar false*/
    return true;
}
