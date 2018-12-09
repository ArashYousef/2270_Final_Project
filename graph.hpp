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
    int severity; //scale from 0-10
    int fuel; //scale from 1-5
    int structures;
    int contain; //scale 0-100
    int windSpeed;
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

    void simulateFire();
    //function to simulate the spread of fire

    void movePilot(std::string name);

    void fightFire();

    //void printDFS();
    //TODO: Might not need this function

    void setAllVerticesUnvisited();
    //pretty self explanatory

  private:
    std::vector<vertex> vertices; //stores vertices
    Pilot * pilot;
    vertex *findVertex(std::string name);
    //finds a desired vertex

    // void BFTraversalLabel(std::string startingCity, int distID);
    //
    // void DFTraversal(vertex *v);
    //TODO: Might not need these functions

};

#endif
