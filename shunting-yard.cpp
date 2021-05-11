//7 May 2021 - Mark Zhang - Shunting Yard - Algorithm that converts user's input in infix to postfix or prefix notation
//the user can choose to which notation to recieve output, the program will output the equation in the given notation and then
//create and print a binary expression tree from the postfix notation of the original input

#include <iostream>
#include <ctype.h>
#include <cstring>
#include "node.h"
#include "stack.h"

//NOTE: stack class is a linked list that can act as both a stack and a queue

using namespace std;

//function declarations

int checkPrecedence(char op);
node* makeBinTree(stack* temp, stack* stack);
void printBinTree(node* root, int level);
void reverseStack(stack* secStack, stack* stack);
void printStack(stack* stack);

int main(){
    while(1){

        //take user input
        cout << "Enter mathematical expression - Please enter all parts of the expression without spaces. Enter [Q] to quit" << endl;
        char* input = new char[50];
        for(int i = 0; i < 50; i++){
            input[i] = 'n';
        }
        cin.clear();
        cin.getline(input, 50);
        if(input[0] == 'Q'){
            break;
        }

        //output queue and operator queue
        stack* output = new stack();
        stack* op = new stack();
        int i = 0;

        //implement the shunting yard algorithm
        while(input[i] != 'n'){
            char temp = input[i];
            if(temp != 'n'){
                if(isdigit(temp)){
                    cout << temp << " is a digit" << endl;
                    node* newNode = new node(temp);
                    output->push(newNode);
                }
                else if(temp == '+' || temp == '-' || temp == '*' || temp == 'x' || temp == '/' || temp == '^'){
                    cout << temp << " is an operator" << endl;
                    while(op->peek() != NULL 
                    && ((checkPrecedence(op->peek()->getValue()) > checkPrecedence(temp))
                    || (checkPrecedence(op->peek()->getValue()) == checkPrecedence(temp) && temp != '^')) 
                    && op->peek()->getValue() != '('){
                        node* n = new node(op->pop()->getValue());
                        output->push(n);
                    }
                    node* newNode = new node(temp);
                    op->push(newNode);
                }
                else if(temp == '('){
                    cout << temp << " is a left parenthesis" << endl;
                    node* newNode = new node(temp);
                    op->push(newNode);
                }
                else if(temp == ')'){
                    cout << temp << " is a right parenthesis" << endl;
                    while(op->peek()->getValue() != '('){
                        if(op->peek()->getValue() != '('){
                            node* n = new node(op->pop()->getValue());
                            output->push(n);
                        }
                    }
                    if(op->peek()->getValue() == '('){
                        op->pop();
                    }
                }
            }
            i++;
        }
        //if the entire input has been read, push all the remaining operators onto the output queue
        while(op->peek() != NULL){
            node* n = new node(op->pop()->getValue());
            output->push(n);
        }
        //at this point, the output queue, if read from head is in prefix notation
        //if read in the opposite direction, it is in postfix notation

        //ask the user to choose notation
        cout << "choose a notation for output: postfix, prefix, infix" << endl;
        stack* output2 = new stack();
        stack* tempstack = new stack();
        char* input2 = new char[10];
        cin.clear();
        cin.getline(input2, 10);
        if(strcmp(input2, "postfix") == 0){
            reverseStack(output2, output);
            cout << "\nPOSTFIX NOTATION: " << endl;
            printStack(output2);
            node* root = makeBinTree(tempstack, output2);
            cout << "\nBINARY EXPRESSION TREE: " << endl;
            printBinTree(root, 0);
        }
        else if(strcmp(input2, "prefix") == 0){
            cout << "\nPREFIX NOTATION: " << endl;
            printStack(output);
            reverseStack(output2, output);
            node* root = makeBinTree(tempstack, output2);
            cout << "\nBINARY EXPRESSION TREE: " << endl;
            printBinTree(root, 0);
        }
        else if(strcmp(input2, "infix") == 0){
            cout << "\nINFIX NOTATION: " << endl;
            cout << input << endl;
            reverseStack(output2, output);
            node* root = makeBinTree(tempstack, output2);
            cout << "\nBINARY EXPRESSION TREE: " << endl;
            printBinTree(root, 0);
        }
    }
    return 0;
}

//function that evaluates the precedence of each operator as per the shunting yard algorithm
int checkPrecedence(char op){
    if(op == '^'){
        return 4;
    }
    else if(op == 'x' || op == '*' || op == '/'){
        return 3;
    }
    else if(op == '+' || op == '-'){
        return 2;
    }
    else{
        return 0;
    }
}

//function that takes in stack and storing the reversed stack to secStack
void reverseStack(stack* secStack, stack* stack){
    while (stack->getSize() != 0){
        secStack->push(stack->pop());
    }
}

//creates a binary tree from stack, uses temp as a temporary stack to help create the tree nodes
node* makeBinTree(stack* temp, stack* stack){
    node* read = stack->peek();
    node* root;
    int size = stack->getSize();
    while(size != 0){
        while(isdigit(read->getValue())){
            //push all integers to the stack
            node* n = new node(read->getValue());
            temp->push(n);
            read = read->getNext();
            size--;
        }
        if(read->getValue() == '+', '-', '*', 'x', '/'){
            //when the function comes across an operator, it sets the left and right nodes to the first two nodes on the temp stack
            node* treenode = new node(read->getValue());
            cout << "treenode: " << read->getValue() << endl;
            treenode->setLeft(temp->pop());
            cout << "treenode left:" << treenode->getLeft()->getValue() << endl;
            treenode->setRight(temp->pop());
            cout << "treenode right:" << treenode->getRight()->getValue() << '\n' << endl;
            temp->push(treenode);
            read = read->getNext();
            size--;
            root = treenode;
        }
    }
    cout << "ROOT: " << root->getValue() << '\n' << endl;
    return root;
}

//prints binrary tree with recursion
void printBinTree(node* root, int spacing){
    if(root == NULL){
        return;
    }
    spacing += 10;
    printBinTree(root->getRight(), spacing);
    cout << endl;
    for(int i = 10; i < spacing; i++){
        cout << " ";
    }
    cout << root->getValue() << '\n';
    printBinTree(root->getLeft(), spacing);
}

//prints a stack starting with the head node
void printStack(stack* stack){
    node* temp = stack->peek();
    while(temp != NULL){
        cout << temp->getValue();
        temp = temp->getNext();
    }
    cout << '\n' << endl;
}