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

struct pilot
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
    int severity; //scale from 0-10
    int fuel; //scale from 1-5
    int structures;//number of occupied structures in area
    int contain; //scale 0-100
    bool onFire;
    bool isGone;
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

    void addVertex(std::string name, int fuel, int structures);
    //creates a new vertex

    void displayEdges();
    //prints all the edges of the graph

    void simulateFire(vertex *v);
    //function to simulate the spread of fire

    void movePilot(std::string name);

    void fightFire();

    //void printDFS();
    //TODO: Might not need this function

    void setAllVerticesUnvisited();
    //pretty self explanatory

    //pq constructor
    PriorityQueue(int queueSize);

    //pq deconstructor
    ~PriorityQueue();

    //add item to pq
    void enqueue (std::string _name, int _injurySeverity, int _treatmentTime);

    //take item out
    void dequeue();

    //checks if queue is full
    bool isFull();

    //checks if queue is empty
    bool isEmpty();

  private:
    int maxSize;
    int currentSize;
    std::vector<vertex> vertices; //stores vertices

    vertex *findVertex(std::string name);
    //finds a desired vertex

    //function to calculate severity of fire
    int calcSev();

    // void BFTraversalLabel(std::string startingCity, int distID);
    //
    // void DFTraversal(vertex *v);
    //TODO: Might not need these functions

};

#endif
