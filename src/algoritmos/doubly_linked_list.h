#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "node.h"
#include <iostream>


class DoublyLinkedList {
private:
    node* head;
    node* tail;
    node* current;
    int size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    node* getHead() const;
    void setHead(node* headPtr);
    node* getTail() const;
    void setTail(node* tailPtr);
    node* getCurrent() const;
    void setCurrent(node* currentPtr);
    int getSize() const;

    bool isEmpty() const;
    void insertFirst(Vector2 element);
    void insertLast(Vector2 element);
    void removeFirst();
    void removeLast();

    void moveToNext(node*& currentNode);
    void moveToPrev(node*& currentNode);
    void moveToHead(node*& currentNode);

    void printAllTiles() const;
    bool checkTiles(Vector2 enemigo);
};

#endif // DOUBLY_LINKED_LIST_H
