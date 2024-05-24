#include "ojo_espectral.h"
#include "entidades/jugador.h" // Incluir la cabecera de Player2D

#include <godot_cpp/core/class_db.hpp>
#include "../../godot-cpp/gen/include/godot_cpp/classes/resource_loader.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/variant/utility_functions.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/packed_scene.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/input.hpp"
#include "../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../godot-cpp/gen/include/godot_cpp/classes/tile_map.hpp"

using namespace godot;

void OjoEspectral::_bind_methods() {
    // Registro de métodos y señales
    ClassDB::bind_method(D_METHOD("_on_range_area_body_entered", "body"), &OjoEspectral::_on_range_area_body_entered);
    ADD_SIGNAL(MethodInfo("body_entered_range_area", PropertyInfo(Variant::OBJECT, "body")));
}

OjoEspectral::OjoEspectral() {
    ojo_animation = nullptr;
    range_area = nullptr;
    range_collision = nullptr;
}

OjoEspectral::~OjoEspectral() {}

void OjoEspectral::_ready() {
    ojo_animation = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    range_area = get_node<Area2D>("RangeArea");
    range_collision = range_area->get_node<CollisionShape2D>("RangeCollision");

    if (!ojo_animation) {
        UtilityFunctions::print("Error: AnimatedSprite2D node not found");
        return;
    }

    if (!range_area) {
        UtilityFunctions::print("Error: RangeArea node not found");
        return;
    }

    if (!range_collision) {
        UtilityFunctions::print("Error: RangeCollision node not found");
        return;
    }

    // Conectar la señal de área a nuestro método personalizado
    range_area->connect("body_entered", Callable(this, "_on_range_area_body_entered"));
}

void OjoEspectral::update_animations() {
    ojo_animation->play("idle");
}

void OjoEspectral::_process(double delta) {
    update_animations();
}

void OjoEspectral::_on_range_area_body_entered(Node* body) {
    // Emitir la señal personalizada solo si el cuerpo es de tipo Player2D
    Player2D* player = Object::cast_to<Player2D>(body);
    if (player) {
        emit_signal("body_entered_range_area", body);
    }
}
