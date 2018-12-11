#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "graph.hpp"

using namespace std;

/*Priority queue constructor*/
Graph::PriorityQueue(int iQueueSize){
  maxSize = iQueueSize;
  fireQueue = new vertex[maxSize + 1];
  currentSize = 0;
}

/*Priority queue deconstructor*/
// Graph::~PriorityQueue(){
//   delete[] fireQueue;
// }

/*Function to put a new item into the pq*/
void Graph::enqueue(vertex *location){
  if(!isFull()){
    currentSize++;
    fireQueue[currentSize] = location;
    repairUpward(currentSize);
  }else{
    cout<<"Queue is Full"<<endl;
  }
}

/*function to remove a fire from the pq*/
void Graph::dequeue(){
  if(isEmpty()){
    cout<<"Queue empty, cannot dequeue an item."<<endl;
    return;
  }else{
    fireQueue[1] = fireQueue[currentSize];
    currentSize--;
    repairDownward(1);
  }
}

// std::string PriorityQueue::peekName(){
//   if(!isEmpty()){
//     return (priorityQueue[1].name);
//   }
//   return NULL;
// }
//
// int PriorityQueue::peekInjurySeverity(){
//   if(!isEmpty()){
//     return (priorityQueue[1].injurySeverity);
//   }
//   return 0;
// }
//
// int PriorityQueue::peekTreatmentTime(){
//   if(!isEmpty()){
//     return(priorityQueue[1].treatmentTime);
//   }
//   return 0;
// }


/*Function to check if pq is full*/
bool Graph::isFull(){
  if(currentSize == maxSize){
    return true;
  }else{
    return false;
  }
}

/*Function to check if pq is empty*/
bool Graph::isEmpty(){
  if(currentSize < 1){
    return true;
  }else{
    return false;
  }
}

/*Funtion used to swap a two nodes*/
void swap(vertex* fireQueue, int childI, int parentI){
  PatientNode temp = fireQueue[childI];
  fireQueue[childI] = fireQueue[parentI];
  fireQueue[parentI] = temp;
}

/*Funtion to fix queue after adding a new item*/
void Graph::repairUpward(int nodeIndex){
  int tempSize = nodeIndex;
  if(!isEmpty()){
    while(tempSize != 1){
      if(fireQueue[tempSize]->severity == fireQueue[tempSize/2]->severity){
        if(fireQueue[tempSize/2]->contain < fireQueue[tempSize]->contain){
          swap(fireQueue, tempSize, tempSize/2);
        }
      }
      else if(fireQueue[tempSize]->severity > fireQueue[tempSize/2]->severity){
        swap(fireQueue, tempSize/2, tempSize);
      }
      tempSize = tempSize/2;
    }
  }
}

/*Function to reorder the pq after removal or updating severity and containment*/
void Graph::repairDownward(int nodeIndex){
  int tempIndex = nodeIndex, tempIndex2 = 0;
  while(tempIndex*2 <= currentSize){
    if(tempIndex*2 == currentSize){
      if(fireQueue[tempIndex]->severity == fireQueue[tempIndex*2]->severity){
        if(fireQueue[tempIndex*2]->contain > fireQueue[tempIndex]->contain){
          swap(fireQueue, tempIndex, tempIndex*2);
        }
        return;
      }
      else if(fireQueue[tempIndex]->severity < fireQueue[tempIndex*2]->severity){
        swap(priorityQueue, tempIndex, tempIndex*2);
        return;
      }
      return;
    }else{
      if(fireQueue[tempIndex*2]->severity == fireQueue[tempIndex*2+1]->severity){
        tempIndex2 = (fireQueue[tempIndex*2+1]->contain < priorityQueue[tempIndex*2]->contain) ? (tempIndex*2) : (tempIndex*2+1);
      }
      else if(fireQueue[tempIndex*2]->severity > fireQueue[tempIndex*2+1]->severity){
        tempIndex2 = tempIndex*2;
      }else{
        tempIndex2 = tempIndex*2+1;
      }
      if(fireQueue[tempIndex]->severity < fireQueue[tempIndex2]->severity){
        swap(fireQueue, tempIndex, tempIndex2);
      }
      else if(fireQueue[tempIndex2]->severity == fireQueue[tempIndex]->severity){
        if(fireQueue[tempIndex]->contain < priorityQueue[tempIndex2]->contain){
          swap(fireQueue, tempIndex, tempIndex2);
        }
      }
      tempIndex = tempIndex2;
    }
  }
}
