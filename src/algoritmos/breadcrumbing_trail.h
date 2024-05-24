#ifndef BREADCRUMBING_TRAIL_H
#define BREADCRUMBING_TRAIL_H

#include "tilemaps.h"

#include "../../godot-cpp/include/godot_cpp/variant/vector2.hpp"
#include "../../godot-cpp/gen/include/godot_cpp/classes/node.hpp"


using namespace godot;
class BreadcrumbTrail : public Node {
    GDCLASS(BreadcrumbTrail, Node);

private:
    Vector2 last_positions[10];
    int current_index;

protected:
    static void _bind_methods();

public:
    BreadcrumbTrail();

    void _process(double delta);
    void add_position(Vector2 position);
    Vector2 get_position(int index);
};



#endif //BREADCRUMBING_TRAIL_H
