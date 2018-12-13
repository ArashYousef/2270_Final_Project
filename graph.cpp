/*
CSCI 2270
Arash Yousefzadeh
Brandon Hernandez
Final Project
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include "graph.hpp"
#include <stdlib.h>

using namespace std;

/*Function to create a new vertex*/
void Graph::addVertex(string name, int fuel, int structures, int windSpeed)
{
  vertex v;
  v.name = name;
  v.structures = structures;
  v.fuel = fuel;
  v.windSpeed = windSpeed;
  vertices.push_back(v);
}

/*Function to add a new edge the a vertices*/
void Graph::addEdge(string v1, string v2, int distance)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == v1)
    {
      for(int j = 0; j < vertices.size(); j++)
      {
        if(vertices[j].name == v2 && i != j)
        {
          Edge e;
          e.v = &vertices[j];
          e.distance = distance;
          vertices[i].Edges.push_back(e);
        }
      }
    }
  }
}

/*Function to calculate the fires severity*/
int Graph::calcSev(vertex* location)
{
  int severity = 0;
  severity += location->structures + location->fuel + location->windSpeed;
  return severity;
}

//Add containment
//Redo code to run through all nodes within function
void Graph::simulateFire()
{
  for(int j = 0; vertices.size(); j++)
  {
    if(!vertices[j].onFire)
    {
      int chance = 0;
      for(int i = 0; vertices[j].Edges.size(); i++)
      {
        chance += vertices[j].Edges[i].v->severity;
      }
      chance += vertices[j].fuel;
      int random = rand() % chance + 1;
        if(chance/2 >= random)
      {
        vertices[j].onFire = true;
        vertices[j].severity = vertices[j].structures + vertices[j].fuel + vertices[j].windSpeed;
        return;
      }
    }
    else
    {
      int random = rand() % 10 + 1;
      int chance = random + vertices[j].fuel;
      if(chance >= 10)
      {
        vertices[j].severity++;
      }
    }
  }
}

/*Funtion to update pilot competetion*/
void Graph::movePilot(std::string name)
{
  pilot->v = findVertex(name);
}

/*Update the containment after fighting fire*/
void Graph::fightFire()
{
  pilot->v->contain += 5;
}

/*Function to print edges*/
void Graph::displayEdges()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    cout << vertices[i].name << "-->";
    for(int j = 0; j < vertices[i].Edges.size(); j++)
    {
      if(j != vertices[i].Edges.size() - 1)
      {
        cout << vertices[i].Edges[j].v->name << " (" << vertices[i].Edges[j].distance << " miles)" <<  "***";
      }
      else
      {
        cout << vertices[i].Edges[j].v->name << " (" << vertices[i].Edges[j].distance << " miles)";
      }
    }
    cout << endl;
  }
}

/*Fucntion to clear all veritces*/
void Graph::setAllVerticesUnvisited()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
}

/*Function to find a vertex*/
vertex* Graph::findVertex(string name)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == name)
    {
      return &vertices[i];
    }
  }
}

/*Graph constructor*/
Graph::Graph()
{
  vector<vertex> vertices;
}

/*Graph desconstructor*/
Graph::~Graph()
{
  while(!vertices.empty())
  {
    vertices.pop_back();
  }
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

/*Priority queue constructor*/
Graph::PriorityQueue(int iQueueSize){
  maxSize = iQueueSize;
  fireQueue = new vertex[maxSize + 1];
  currentSize = 0;
}

/*Function to put a new item into the pq*/
void Graph::enqueue(vertex *location){
  if(!isFull()){
    currentSize++;
    //fireQueue[currentSize] = location;
    repairUpward(currentSize);
  }else{
    cout<<"Queue is Full"<<endl;
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



int main(int argc, char const *argv[])
{
  Graph landMap;
  Graph skyMap;

  landMap.addVertex("Rothstown", 3, 150, 23);
  landMap.addVertex("BoizTrailerPark", 3, 48, 25);
  landMap.addVertex("Fancytown", 3, 13, 24);
  landMap.addVertex("IndustrialZone", 4, 75, 15);
  landMap.addVertex("WestForest", 5, 2, 7);
  landMap.addVertex("SouthForest", 5, 0, 16);
  landMap.addVertex("EastForest", 5, 3, 29);
  landMap.addVertex("Mountains", 1, 1, 13);
  landMap.addVertex("Southtown", 3, 89, 8);

  skyMap.addVertex("Rothstown", 3, 150, 23);
  skyMap.addVertex("BoizTrailerPark", 3, 48, 25);
  skyMap.addVertex("Fancytown", 3, 13, 24);
  skyMap.addVertex("IndustrialZone", 4, 75, 15);
  skyMap.addVertex("WestForest", 5, 2, 7);
  skyMap.addVertex("SouthForest", 5, 0, 16);
  skyMap.addVertex("EastForest", 5, 3, 29);
  skyMap.addVertex("Mountains", 1, 1, 13);
  skyMap.addVertex("Southtown", 3, 89, 8);

  landMap.addEdge("Rothstown", "BoizTrailerPark", 5);
  landMap.addEdge("Rothstown", "Fancytown", 5);
  landMap.addEdge("Rothstown", "IndustrialZone", 7);

  landMap.addEdge("BoizTrailerPark", "Rothstown", 5);
  landMap.addEdge("BoizTrailerPark", "WestForest", 5);
  landMap.addEdge("BoizTrailerPark", "IndustrialZone", 5);
  landMap.addEdge("BoizTrailerPark", "Fancytown", 7);
  landMap.addEdge("BoizTrailerPark", "SouthForest", 7);

  landMap.addEdge("WestForest", "SouthForest", 5);
  landMap.addEdge("WestForest", "BoizTrailerPark", 5);
  landMap.addEdge("WestForest", "IndustrialZone", 7);

  landMap.addEdge("Fancytown", "Rothstown", 5);
  landMap.addEdge("Fancytown", "IndustrialZone", 5);
  landMap.addEdge("Fancytown", "Mountains", 5);
  landMap.addEdge("Fancytown", "BoizTrailerPark", 7);
  landMap.addEdge("Fancytown", "EastForest", 7);

  landMap.addEdge("IndustrialZone", "Fancytown", 5);
  landMap.addEdge("IndustrialZone", "BoizTrailerPark", 5);
  landMap.addEdge("IndustrialZone", "EastForest", 5);
  landMap.addEdge("IndustrialZone", "SouthForest", 5);
  landMap.addEdge("IndustrialZone", "Rothstown", 7);
  landMap.addEdge("IndustrialZone", "WestForest", 7);
  landMap.addEdge("IndustrialZone", "Southtown", 7);
  landMap.addEdge("IndustrialZone", "Mountains", 7);

  landMap.addEdge("SouthForest", "WestForest", 5);
  landMap.addEdge("SouthForest", "IndustrialZone", 5);
  landMap.addEdge("SouthForest", "Southtown", 5);
  landMap.addEdge("SouthForest", "BoizTrailerPark", 7);
  landMap.addEdge("SouthForest", "EastForest", 7);

  landMap.addEdge("Mountains", "Fancytown", 5);
  landMap.addEdge("Mountains", "IndustrialZone", 7);
  landMap.addEdge("Mountains", "EastForest", 5);

  landMap.addEdge("EastForest", "Mountains", 5);
  landMap.addEdge("EastForest", "IndustrialZone", 5);
  landMap.addEdge("EastForest", "Southtown", 5);
  landMap.addEdge("EastForest", "Fancytown", 7);
  landMap.addEdge("EastForest", "SouthForest", 7);

  landMap.addEdge("Southtown", "EastForest", 5);
  landMap.addEdge("Southtown", "SouthForest", 5);
  landMap.addEdge("Southtown", "IndustrialZone", 7);




  skyMap.addEdge("Rothstown", "BoizTrailerPark", 5);
  skyMap.addEdge("Rothstown", "Fancytown", 5);
  skyMap.addEdge("Rothstown", "IndustrialZone", 7);
  skyMap.addEdge("Rothstown", "WestForest", 10);
  skyMap.addEdge("Rothstown", "SouthForest", 11);
  skyMap.addEdge("Rothstown", "Mountains", 10);
  skyMap.addEdge("Rothstown", "EastForest", 11);
  skyMap.addEdge("Rothstown", "Southtown", 14);

  skyMap.addEdge("BoizTrailerPark", "Rothstown", 5);
  skyMap.addEdge("BoizTrailerPark", "WestForest", 5);
  skyMap.addEdge("BoizTrailerPark", "IndustrialZone", 5);
  skyMap.addEdge("BoizTrailerPark", "Fancytown", 7);
  skyMap.addEdge("BoizTrailerPark", "SouthForest", 7);
  skyMap.addEdge("BoizTrailerPark", "Mountains", 11);
  skyMap.addEdge("BoizTrailerPark", "EastForest", 10);
  skyMap.addEdge("BoizTrailerPark", "Southtown", 11);

  skyMap.addEdge("WestForest", "SouthForest", 5);
  skyMap.addEdge("WestForest", "BoizTrailerPark", 5);
  skyMap.addEdge("WestForest", "IndustrialZone", 7);
  skyMap.addEdge("WestForest", "Rothstown", 10);
  skyMap.addEdge("WestForest", "Fancytown", 11);
  skyMap.addEdge("WestForest", "Mountains", 14);
  skyMap.addEdge("WestForest", "EastForest", 11);
  skyMap.addEdge("WestForest", "Southtown", 10);

  skyMap.addEdge("Fancytown", "Rothstown", 5);
  skyMap.addEdge("Fancytown", "IndustrialZone", 5);
  skyMap.addEdge("Fancytown", "Mountains", 5);
  skyMap.addEdge("Fancytown", "BoizTrailerPark", 7);
  skyMap.addEdge("Fancytown", "EastForest", 7);
  skyMap.addEdge("Fancytown", "SouthForest", 10);
  skyMap.addEdge("Fancytown", "Southtown", 11);
  skyMap.addEdge("Fancytown", "WestForest", 11);

  skyMap.addEdge("IndustrialZone", "Fancytown", 5);
  skyMap.addEdge("IndustrialZone", "BoizTrailerPark", 5);
  skyMap.addEdge("IndustrialZone", "EastForest", 5);
  skyMap.addEdge("IndustrialZone", "SouthForest", 5);
  skyMap.addEdge("IndustrialZone", "Rothstown", 7);
  skyMap.addEdge("IndustrialZone", "WestForest", 7);
  skyMap.addEdge("IndustrialZone", "Southtown", 7);
  skyMap.addEdge("IndustrialZone", "Mountains", 7);

  skyMap.addEdge("SouthForest", "WestForest", 5);
  skyMap.addEdge("SouthForest", "IndustrialZone", 5);
  skyMap.addEdge("SouthForest", "Southtown", 5);
  skyMap.addEdge("SouthForest", "BoizTrailerPark", 7);
  skyMap.addEdge("SouthForest", "EastForest", 7);
  skyMap.addEdge("SouthForest", "Rothstown", 11);
  skyMap.addEdge("SouthForest", "Fancytown", 10);
  skyMap.addEdge("SouthForest", "Mountains", 11);

  skyMap.addEdge("Mountains", "Fancytown", 5);
  skyMap.addEdge("Mountains", "IndustrialZone", 7);
  skyMap.addEdge("Mountains", "EastForest", 5);
  skyMap.addEdge("Mountains", "Rothstown", 10);
  skyMap.addEdge("Mountains", "Southtown", 10);
  skyMap.addEdge("Mountains", "WestForest", 14);
  skyMap.addEdge("Mountains", "SouthForest", 11);
  skyMap.addEdge("Mountains", "BoizTrailerPark", 11);

  skyMap.addEdge("EastForest", "Mountains", 5);
  skyMap.addEdge("EastForest", "IndustrialZone", 5);
  skyMap.addEdge("EastForest", "Southtown", 5);
  skyMap.addEdge("EastForest", "Fancytown", 7);
  skyMap.addEdge("EastForest", "SouthForest", 7);
  skyMap.addEdge("EastForest", "Rothstown", 11);
  skyMap.addEdge("EastForest", "BoizTrailerPark", 10);
  skyMap.addEdge("EastForest", "WestForest", 11);

  skyMap.addEdge("Southtown", "EastForest", 5);
  skyMap.addEdge("Southtown", "SouthForest", 5);
  skyMap.addEdge("Southtown", "IndustrialZone", 7);
  skyMap.addEdge("Southtown", "WestForest", 10);
  skyMap.addEdge("Southtown", "Mountains", 10);
  skyMap.addEdge("Southtown", "BoizTrailerPark", 11);
  skyMap.addEdge("Southtown", "Fancytown", 11);
  skyMap.addEdge("Southtown", "Rothstown", 14);

  skyMap.movePilot("Southtown");

  //add towns to the queue
  landMap.enqueue("Rothstown");
  landMap.enqueue("BoizTrailerPark");
  landMap.enqueue("Fancytown");
  landMap.enqueue("IndustrialZone");
  landMap.enqueue("WestForest");
  landMap.enqueue("Southtown");
  landMap.enqueue("EastForest");
  landMap.enqueue("Mountains");
  landMap.enqueue("Southtown");

  int i;
  while(1)
  {
    string choice;
    landMap.simulateFire();//simulate the fire
    //check to see if fire has been contained
    for(i=1;i<=currentSize;i++){
      if(fireQueue[i]->contain == 100){
      landMap.dequeue(fireQueue[i]);
      }
    }
    landMap.reheap(1);//fix the priority queue with new values from simulation
    cin >> choice;//get user input for pilot motion
    landMap.movePilot(choice);//move pilot to choice
    landMap.fightFire();//update after fighting fire

  }
  return 0;
}
