#ifndef NODE_H
#define NODE_H

class node
{
private:
    char value;
    node* next;
public:
    node(char newValue);
    char getValue();
    void setValue(char data);
    node* getNext();
    void setNext(node* newNext);
    ~node();
};

#endif