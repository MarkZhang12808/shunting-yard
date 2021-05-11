//Mark Zhang - .cpp file for node class
//node can be used create a single-linked-list where each node points to the next node
//or a double-linked-list where each node points to both a left and right node
#include "node.h"
#include <iostream>

node::node(char data){
    value = data;
    next = NULL;
    left = NULL;
    right = NULL;
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

node* node::getLeft(){
    return left;
}

node* node::getRight(){
    return right;
}

void node::setNext(node* newNext){
    next = newNext;
}

void node::setLeft(node* n){
    left = n;
}

void node::setRight(node* n){
    right = n;
}

node::~node(){
    delete &value;
}