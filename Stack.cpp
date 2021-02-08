/* 8/31/98 Mary Elaine Califf
 * a C++ linked list implementation of stacks
 */

// Modified:
//   8/20/2003 by Mary Elaine Califf
//      Changed to ANSI C++
// revised 12/25/20
// Tre Blankenship and Mary Elaine Califf
//Implementation of a stack of integers

#include <iostream>
#include "Stack.h"

using namespace std;

// Constructor
Stack::Stack()
{
  topNode = nullptr;
}

// Copy Constructor
Stack::Stack(const Stack& rep){
  copy(rep);
}

// Destructor
Stack::~Stack(){
  clear();
}

// = overload
Stack& Stack::operator=(const Stack& rep){
  if(this != &rep){
    clear();
    copy(rep);
  }
  return *this;
}

bool Stack::push(int newValue)
{
  if(IsEmpty()){
    topNode = new Node(newValue, nullptr);
  }
  else{
    Node *newNode = new Node(newValue, topNode);
    topNode = newNode;
  }
  return true;
}

int Stack::pop()
{
  int numRemoved = topNode->dataVal;

  Node *temp = topNode;
  topNode = topNode->next;
  delete temp;

  return numRemoved;
}

int Stack::top(){
  return topNode->dataVal;
}

bool Stack::IsEmpty(){
  if(topNode == nullptr) return true;
  else return false;
}

void Stack::copy(const Stack& rep){
  if(rep.topNode != nullptr){
    Node *temp = rep.topNode;
    topNode = new Node(temp->dataVal, nullptr);
    Node *prevNode = topNode;
    temp = temp->next;
    while(temp != nullptr){
      Node *newNode = new Node(temp->dataVal, nullptr);
      prevNode->next = newNode;
      prevNode = prevNode->next;
      temp = temp->next;
    }
  }
}

void Stack::clear(){
  while(!IsEmpty()){
    pop();
  }
}
