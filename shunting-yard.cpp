#include <iostream>
#include <ctype.h>
#include <cstring>
#include "node.h"
#include "stack.h"

using namespace std;

int checkPrecedence(char op);
//stack* createPrefixStack(char* input);
node* makeBinTree(stack* temp, stack* stack);
void printBinTree(node* root);
void reverseStack(stack* secStack, stack* stack);
void printStack(stack* stack);

int main(){
    while(1){
        cout << "Enter mathematical expression" << endl;
        char* input = new char[50];
        for(int i = 0; i < 50; i++){
            input[i] = 'n';
        }
        cin.clear();
        cin.getline(input, 50);
        if(input[0] == 'Q'){
            break;
        }
        stack* output = new stack();
        stack* op = new stack();
        int i = 0;
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
        while(op->peek() != NULL){
            node* n = new node(op->pop()->getValue());
            output->push(n);
        }
        cout << "choose a notation for output: postfix, prefix, infix" << endl;
        stack* output2 = new stack();
        stack* tempstack = new stack();
        char* input2 = new char[10];
        cin.clear();
        cin.getline(input2, 10);
        if(strcmp(input2, "postfix") == 0){
            reverseStack(output2, output);
            printStack(output2);
            makeBinTree(tempstack, output2);
        }
        else if(strcmp(input2, "prefix") == 0){
            printStack(output);
        }
        else if(strcmp(input2, "infix") == 0){
            cout << input << endl;
        }
    }
    return 0;
}

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

//stack* createPrefixStack(char* input){}

void reverseStack(stack* secStack, stack* stack){
    while (stack->getSize() != 0){
        secStack->push(stack->pop());
    }
}

node* makeBinTree(stack* temp, stack* stack){
    node* read = stack->peek();
    node* root;
    int size = stack->getSize();
    while(size != 0){
        while(isdigit(read->getValue())){
            node* n = new node(read->getValue());
            temp->push(n);
            cout << read->getValue() << " pushed onto stack" << endl;
            read = read->getNext();
            size--;
        }
        if(read->getValue() == '+', '-', '*', 'x', '/'){
            cout << "stack: " << endl;
            printStack(temp);
            node* treenode = new node(read->getValue());
            cout << "treenode: " << read->getValue() << endl;
            treenode->setLeft(temp->pop());
            cout << "treenode left:" << treenode->getLeft()->getValue() << endl;
            treenode->setRight(temp->pop());
            cout << "treenode right:" << treenode->getRight()->getValue() << endl;
            temp->push(treenode);
            cout << "stack after: " << endl;
            printStack(temp);
            read = read->getNext();
            size--;
            root = treenode;
        }
    }
    cout << root->getValue() << endl;
    return root;
}

void printBinTree(node* root){

}

void printStack(stack* stack){
    node* temp = stack->peek();
    while(temp != NULL){
        cout << temp->getValue();
        temp = temp->getNext();
    }
    cout << endl;
}