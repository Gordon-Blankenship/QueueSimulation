/** 02/03/2021 - Program01
 *  Postfix Expression Evaluation
 *  by Tre Blankenship
 *  IT 279 Sec001
 * 
 *  This program takes input from a 
 *  User in Postfix notation and then
 *  executes the code and returns the
 *  evaluated number.
*/
#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

int main(){
    Stack stack;
    string expression = "";
    cout<<"Enter Expression (Q to quit): ";
    getline(cin, expression);
    while(expression != "Q"){
        string temp;
        int num, num1, num2;
        int total = 0;
        for(char x : expression){
            switch(x){
                case ' ':
                    if(temp != ""){
                        num = stoi(temp);
                        stack.push(num);
                        temp = "";
                    }
                    break;
                case '+':
                    num2 = stack.pop();
                    num1 = stack.pop();
                    total = num1 + num2;
                    stack.push(total);
                    break;
                case '-':
                    num2 = stack.pop();
                    num1 = stack.pop();
                    total = num1 - num2;
                    stack.push(total);
                    break;
                case '*':
                    num2 = stack.pop();
                    num1 = stack.pop();
                    total = num1 * num2;
                    stack.push(total);
                    break;
                case '/':
                    num2 = stack.pop();
                    num1 = stack.pop();
                    total = num1 / num2;
                    stack.push(total);
                    break;
                default:
                    temp.push_back(x);
                    break;

            }
        }
        cout<<"Result: "<<stack.top()<<endl;
        expression = "";
        stack.~Stack();
        cout<<"Enter Expression (Q to quit): ";
        getline(cin, expression);
    }

    return 0;
}