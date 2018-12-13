/*
CSCI 2270
Arash Yousefzadeh
Brandon Hernandez
Final Project
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

struct vertex;

struct Pilot
{
  vertex *v;
};

struct Edge
{
    vertex *v;
    int distance;
};

struct vertex //add containment
{
    std::string name;
    int severity;
    int fuel; //scale from 1-5
    int structures;//number of occupied structures in area
    int contain; //scale 0-100
    int windSpeed;// scale of 1-30
    bool onFire;
    bool visited;
    std::vector<Edge> Edges;
};
/*
Each vertex will represent a given location.
All data related to the fire will be stored within these.
*/
class Graph
{
  public:
    Graph(); //constructor

    ~Graph(); //destructor

    void addEdge(std::string v1, std::string v2, int distance);
    //creates an edge between two nodes

    void addVertex(std::string name, int fuel, int structures, int windSpeed);
    //creates a new vertex

    void displayEdges();
    //prints all the edges of the graph

    void simulateFire();
    //function to simulate the spread of fire

    void movePilot(std::string name);

    void fightFire();

    void setAllVerticesUnvisited();
    //pretty self explanatory

    //pq constructor
    PriorityQueue(int queueSize);


    //add item to pq
    void enqueue (vertex* location);

    //take item out
    void dequeue();

    void repairUpward(int nodeIndex);

    //checks if queue is full
    bool isFull();

    //checks if queue is empty
    bool isEmpty();

    int currentSize;
    vertex * fireQueue;
  private:
    int maxSize;

    std::vector<vertex> vertices; //stores vertices
    Pilot * pilot;
    vertex *findVertex(std::string name);
    //finds a desired vertex

    //function to calculate severity of fire
    int calcSev(vertex* location);

};

#endif
