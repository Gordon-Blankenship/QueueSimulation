/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of stacks
 * 
 * Revised 12/25/2020
 */
// Tre Blankenship and Mary Elaine Califf
//Header file for a stack of integers

#ifndef STACK_H
#define STACK_H

struct Node{
    int dataVal;
    Node *next;

    Node(int data, Node *nextPtr) : dataVal(data), next(nextPtr) {}
};

class Stack
{

public:
  Stack(); // constructor
  Stack(const Stack& rep); // copy constructor
  ~Stack(); // destructor
  Stack& operator=(const Stack& rep); // = overload

  // add a new value to the stack
  // fails and return false if the stack is full
  bool push(int newValue);

  // pops top item off of the stack
  // Precondition: stack must not be empty
  int pop();

  // return item at the top of the stack without removing it
  // Precondition: stack must not be empty
  int top();

  // checks if the topNode is nullptr
  // returns true if topNode == nullptr
  bool IsEmpty();

private:
  Node *topNode;
  void copy(const Stack& rep); // copy method
  void clear();
};

#endif
