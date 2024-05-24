#ifndef GDEXTENSION_CPP_EXAMPLE_CHOCOBO_H
#define GDEXTENSION_CPP_EXAMPLE_CHOCOBO_H

#include "../../../godot-cpp/gen/include/godot_cpp/classes/character_body2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/animated_sprite2d.hpp"
#include "../../../godot-cpp/gen/include/godot_cpp/classes/node2d.hpp"

namespace godot {
    class Chocobo : public CharacterBody2D {
        GDCLASS(Chocobo, CharacterBody2D);

    private:
        int vidas;

        AnimatedSprite2D* animated_run_right;
        AnimatedSprite2D* animated_run_left;

        Vector2 player_position;

        Vector2 current_direction;
        Vector2 last_horizontal_direction;

    protected:
        static void _bind_methods();

    public:
        Chocobo();
        ~Chocobo();

        void _ready() override;
        void _process(double delta) override;
        void _on_player_position_changed(Vector2 new_position);
        bool check_line_of_sight(Vector2 target_position);
        void update_animations();
    };
}

#endif //GDEXTENSION_CPP_EXAMPLE_CHOCOBO_H
