#include "treenode.h"
#include <iostream>

treenode::treenode(char* newValue)
{
    value = newValue;
    left = NULL;
    right = NULL;
}

void treenode::setValue(char* newValue){
    value = newValue;
}

char* treenode::getValue(){
    return value;
}

treenode* treenode::getLeft(){
    return left;
}

treenode* treenode::getRight(){
    return right;
}

void treenode::setLeft(treenode* l){
    left = l;
}

void treenode::setRight(treenode* r){
    right = r;
}

treenode::~treenode()
{
}
