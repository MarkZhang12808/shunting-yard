#include <iostream>
#include <ctype.h>
#include <cstring>
#include "treenode.h"
#include "node.h"
#include "stack.h"

using namespace std;

int checkPrecedence(char op);
void printStackPostfix(stack* stack);
void printStackPrefix(stack* stack);

int main(){
    while(1){
        cout << "Enter mathematical expression" << endl;
        char* input = new char[50];
        for(int i = 0; i < 50; i++){
            input[i] = 'n';
        }
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
                    /*
                    if(op->peek()->getValue() == '+' || op->peek()->getValue() == '-' || op->peek()->getValue() == '*' 
                    || op->peek()->getValue() == 'x' || op->peek()->getValue() == '/' || op->peek()->getValue() == '^'){
                        node* n = new node(op->pop()->getValue());
                        output->push(n);
                    }
                    */
                }
            }
            /*
            cout << '\n' << "OPERATOR STACK" << endl;
            printStackPrefix(op);
            cout << "OUTPUT QUEUE" << endl;
            printStackPrefix(output);
            cout << '\n' << endl;
            */
            i++;
        }
        while(op->peek() != NULL){
            node* n = new node(op->pop()->getValue());
            output->push(n);
        }
        cout << "choose a notation for output: postfix, prefix, infix" << endl;
        char* input2;
        cin >> input2;
        if(strcmp(input2, "postfix") == 0){
            printStackPostfix(output);
        }
        else if(strcmp(input2, "prefix") == 0){
            printStackPrefix(output);
        }
        else if(strcmp(input2, "infix") == 0){

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

void printStackPostfix(stack* st){
    stack* stack = st;
    cout << "Postfix notation: " << endl;
    while (stack->getSize() != 0)
    {
        cout << stack->dequeue();
    }
    cout << '\n' << endl;
}


void printStackPrefix(stack* stack){
    node* temp = stack->peek();
    cout << "Prefix notation: " << endl;
    while(temp != NULL){
        cout << temp->getValue();
        temp = temp->getNext();
    }
    cout << endl;
}