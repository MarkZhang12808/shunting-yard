#include "node.h"
#include <iostream>

node::node(char data){
    value = data;
    next = NULL;
}

void node::setValue(char data){
    value = data;
}

char node::getValue(){
    return value;
}

node* node::getNext(){
    return next;
}

void node::setNext(node* newNext){
    next = newNext;
}

node::~node(){
    delete &value;
}