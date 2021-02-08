/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of a queue of integers which may have length of up to 100
 * 
 * Revised 12/25/2020 
 */
// Modified : 02/05/2021
// Tre Blankenship and Mary Elaine Califf S2021
//Header file for a queue of CustomerData objects

#ifndef QUEUE_H
#define QUEUE_H
#include "CustomerData.h"

struct Node{
    CustomerData dataVal;
    Node *next;

    Node(CustomerData data, Node *nextPtr) : dataVal(data), next(nextPtr) {}
};

class Queue
{
public:
  Queue(); // constructor
  ~Queue(); // destructor
  Queue(const Queue& rep); // copy constructor
  Queue &operator=(const Queue& rep); // = overload

  // getter for size
  int getSize();

  // is the queue empty
  bool isEmpty();

  // adds a new value to the queue
  // fails and returns false if the queue is full
  bool enqueue(CustomerData newValue);

  // removes a value from the queue and returns it
  // Precondition: queue must not be empty
  CustomerData dequeue();

  // return item at the front of the queue without removing it
  // Precondtion: queue must not be empty
  CustomerData front();

private:
  Node *firstIn;
  Node *lastIn;
  void clear();
  void copy(const Queue& rep);
};

#endif
