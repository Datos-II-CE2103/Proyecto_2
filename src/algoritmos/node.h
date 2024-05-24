#ifndef NODO_H
#define NODO_H

#include "../../godot-cpp/include/godot_cpp/variant/vector2.hpp"

using namespace godot;

class node {
private:
    Vector2* valueNode;
    node* nextNode;
    node* prevNode;

public:
    node();
    node(Vector2* newValue, node *n, node *p);
    node(Vector2* newValue);

    Vector2* getValueNode() const;
    node* getNextNode() const;
    node* getPrevNode() const;
    void setValueNode(Vector2* value);
    void setNextNode(node *next);
    void setPrevNode(node *prev);
    ~node();
};

#endif
