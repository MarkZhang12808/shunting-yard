#ifndef TREENODE_H
#define TREENODE_H

class treenode
{
private:
    char* value;
    treenode* left;
    treenode* right;
public:
    treenode(char* newValue);
    void setValue(char* newValue);
    char* getValue();
    treenode* getLeft();
    treenode* getRight();
    void setLeft(treenode* l);
    void setRight(treenode* r);
    ~treenode();
};

#endif