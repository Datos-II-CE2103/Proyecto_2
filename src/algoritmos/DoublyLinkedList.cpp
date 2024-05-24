#include "doubly_linked_list.h"
#include <iostream>
#include "node.h"

using namespace godot;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    while (!isEmpty()) {
        removeFirst();
    }
}

node* DoublyLinkedList::getHead() const {
    return head;
}

void DoublyLinkedList::setHead(node* headPtr) {
    this->head = headPtr;
}

node* DoublyLinkedList::getTail() const {
    return tail;
}

void DoublyLinkedList::setTail(node* tailPtr) {
    this->tail = tailPtr;
}

node* DoublyLinkedList::getCurrent() const {
    return current;
}

void DoublyLinkedList::setCurrent(node* currentPtr) {
    this->current = currentPtr;
}

int DoublyLinkedList::getSize() const {
    return size;
}

bool DoublyLinkedList::isEmpty() const {
    return (head == nullptr);
}

void DoublyLinkedList::insertFirst(Vector2* element) {
    node* newNode = new node(element);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->setNextNode(head);
        head->setPrevNode(newNode);
        head = newNode;
    }

    size++;
}

void DoublyLinkedList::insertLast(Vector2* element) {
    node* newNode = new node(element);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->setPrevNode(tail);
        tail->setNextNode(newNode);
        tail = newNode;
    }

    size++;
}

void DoublyLinkedList::removeFirst() {
    if (!isEmpty()) {
        node* temp = head;
        head = head->getNextNode();
        if (head) {
            head->setPrevNode(nullptr);
        }
        delete temp;
        size--;
    }
}

void DoublyLinkedList::removeLast() {
    if (!isEmpty()) {
        node* temp = tail;
        tail = tail->getPrevNode();
        if (tail) {
            tail->setNextNode(nullptr);
        }
        delete temp;
        size--;
    }
}

void DoublyLinkedList::moveToNext(node*& currentNode) {
    if (currentNode->getNextNode() != nullptr) {
        current = currentNode->getNextNode();
    } else {
        current = getHead();
    }
}

void DoublyLinkedList::moveToPrev(node*& currentNode){
    if (currentNode->getPrevNode() != nullptr){
        current = currentNode->getPrevNode();
    } else {
        current = getTail();
    }
}

void DoublyLinkedList::moveToHead(node*& currentNode) {
    if (currentNode != getHead()) {
        node* temp = getHead();
        while (temp->getNextNode() != currentNode) {
            temp = temp->getNextNode();
        }
        temp->setNextNode(currentNode->getNextNode());
        currentNode->setNextNode(getHead());
        setHead(currentNode);
    }
}
