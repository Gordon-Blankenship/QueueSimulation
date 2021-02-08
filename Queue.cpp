/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of queues
 */
// Modifications:
//    8/20/2003 Mary Elaine Califf
//        Changed to ANSI C++
// Revised 02/05/2021
// Tre Blankenship and Mary Elaine Califf S2021
//Implementation of a queue of CustomerData objects

#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue() // constructor
{
  firstIn = nullptr;
  lastIn = nullptr;
}

Queue::~Queue(){ // destructor
  clear();
}

Queue::Queue(const Queue& rep){ // copy constructor
  copy(rep);
}

Queue& Queue::operator=(const Queue& rep){ // = overload
  if(this != &rep){
    clear();
    copy(rep);
  }
  return *this;
}

int Queue::getSize(){
  int counter = 0;
  Node *temp = firstIn;
  while(temp != nullptr){
    counter++;
    temp = temp->next;
  }
  return counter;
}

bool Queue::isEmpty(){
  if(firstIn == nullptr) return true;
  else return false;
}

bool Queue::enqueue(CustomerData newValue) // add newValue to queue
{
  if(isEmpty()){
    firstIn = new Node(newValue, nullptr);
    lastIn = firstIn;
  }
  else{
    lastIn->next = new Node(newValue, nullptr);
    lastIn = lastIn->next;
  }
  return true;
}

CustomerData Queue::dequeue()
{
  CustomerData removed = firstIn->dataVal;
  if(firstIn==lastIn){
    lastIn = nullptr;
    delete firstIn;
    firstIn = nullptr;
  }
  else{
    Node *temp = firstIn;
    firstIn = firstIn->next;
    delete temp;
  }
  return removed;
}

CustomerData Queue::front(){
  CustomerData data = firstIn->dataVal;
  return data;
}

void Queue::clear(){
  while(!isEmpty()){
    dequeue();
  }
}

void Queue::copy(const Queue& rep){
  Node *temp = rep.firstIn;
  firstIn = new Node(temp->dataVal, nullptr);
  lastIn = firstIn;
  Node *prevNode = firstIn;
  temp = temp->next;
  while(temp != nullptr){
    lastIn = new Node(temp->dataVal, nullptr);
    prevNode->next = lastIn;
    prevNode = lastIn;
    temp = temp->next;
  }
}