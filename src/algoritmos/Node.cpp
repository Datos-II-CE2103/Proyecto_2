#include "node.h"

using namespace godot;

node::node() : valueNode(Vector2(0, 0)), nextNode(nullptr), prevNode(nullptr) {}

node::node(Vector2 newValue, node *n, node *p) : valueNode(newValue), nextNode(n), prevNode(p) {}

node::node(Vector2 newValue) : valueNode(newValue), nextNode(nullptr), prevNode(nullptr) {}

Vector2 node::getValueNode() const {
    return valueNode;
}

node* node::getNextNode() const {
    return nextNode;
}

node* node::getPrevNode() const {
    return prevNode;
}

void node::setValueNode(Vector2 value) {
    valueNode = value;
}

void node::setNextNode(node *next) {
    nextNode = next;
}

void node::setPrevNode(node *prev) {
    prevNode = prev;
}

node::~node() {
}
