#include <iostream>
#include "stack.h"
#include "node.h"

stack::stack(){
    head = NULL;
}

node* stack::pop(){
    node* temp = head->getNext();
    node* h = head;
    delete head;
    head = temp;
    size--;
    return h;
}

node* stack::peek(){
    return head;
}

void stack::push(node* n){
    n->setNext(head);
    head = n;
    size++;
}

node* stack::dequeue(){
    node* temp = head;
    node* prev = head;
    while(temp->getNext() != NULL){
        prev = temp;
        temp = temp->getNext();
    }
    node* c = temp;
    prev->setNext(NULL);
    delete temp;
    size--;
    return c;
}

int stack::getSize(){
    return size;
}

stack::~stack(){

}