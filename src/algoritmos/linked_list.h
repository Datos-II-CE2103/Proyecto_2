#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include <iostream>

class LinkedList {
private:
    node* head;
    node* tail;
    node* current;
    int size;

public:
    LinkedList();
    ~LinkedList();

    node* getHead() const;
    void setHead(node* head);
    node* getTail() const;
    void setTail(node* tail);
    node* getCurrent() const;
    void setCurrent(node* current);
    int getSize() const;

    bool isEmpty() const;
    void insertFirst(Vector2* element);
    void insertLast(Vector2* element);
    void removeFirst();
    void removeLast();
    void insertBefore(node* nextNode, Vector2* value);
    void removeFromBeginning();
};

#endif // LINKED_LIST_H
