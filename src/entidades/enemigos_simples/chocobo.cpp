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

    // Conectar la señal del Player2D
    Player2D* player_node = get_node<Player2D>("../main/Player2D");  // Ajusta la ruta según tu escena
    if (player_node) {
        player_node->connect("position_changed", Callable(this, "_on_player_position_changed"));
        player_position = player_node->get_global_position();
    } else {
        UtilityFunctions::print("Error: Player2D node not found");
    }
}

void Chocobo::_process(double delta) {
    update_animations();
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
// Actualiza la posición del jugador cuando cambia
player_position = new_position;
}

bool Chocobo::check_line_of_sight(Vector2 target_position) {
// Implementa Bresenham Line of Sight
// Retorna true si hay línea de visión, de lo contrario retorna false
// Aquí puedes agregar la lógica para verificar si hay obstáculos entre el chocobo y el jugador
// Por ejemplo, puedes usar RayCast2D para verificar si hay obstáculos en el camino
// Si no hay obstáculos, retorna true; de lo contrario, retorna false
return true; // Cambia esto según tu implementación real
}
