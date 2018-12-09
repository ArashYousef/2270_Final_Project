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

void Graph::addVertex(string name)
{
  vertex v;
  v.name = name;
  vertices.push_back(v);
}

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

//Add containment
//Redo code to run through all nodes within function
void Graph::simulateFire(vertex *v)
{
  if(v.isGone)
  {
    return;
  }

  if(!v.onFire)
  {
    int chance = 0;
    for(int i = 0; v.Edges.size(); i++)
    {
      chance += v.Edges[i].v->severity;
    }
    chance += fuel;
    int random = rand() % 30 + 1;
    if(chance >= random)
    {
      v.onFire = true;
      v.severity = 1;
      return;
    }
  }
  else
  {
    int random = rand() % 10 + 1;
    int chance = random + v.fuel;
    if(chance >= 10)
    {
      if(v.severity == 10)
      {
        v.isGone = true;
        v.severity = 0;
        v.onFire = false;
      }
      else
      {
        v.severity++;
      }
    }
  }
}

void Graph::movePilot(std::string name)
{
  pilot.v = findVertex(name);
}

void fightFire();
{
  pilot.v->contain += 5;
}

void Graph::displayEdges()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    cout << vertices[i].district << ":" << vertices[i].name << "-->";
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

// void Graph::BFTraversalLabel(string startingCity, int distID)
// {
//   for(int i = 0; i < vertices.size(); i++)
//   {
//     if(vertices[i].name == startingCity)
//     {
//       vertices[i].visited = true;
//       vertices[i].district = distID;
//       for(int j = 0; j < vertices[i].Edges.size(); j++)
//       {
//         if(!vertices[i].Edges[j].v->visited)
//         {
//           BFTraversalLabel(vertices[i].Edges[j].v->name, distID);
//         }
//       }
//     }
//   }
// }

// void Graph::DFTraversal(vertex* v)
// {
//   v->visited = true;
//   cout << v->name << endl;
//   for(int i = 0; i < v->Edges.size(); i++)
//   {
//     if(!v->Edges[i].v->visited)
//     {
//       DFTraversal(v->Edges[i].v);
//     }
//   }
// }

// void Graph::printDFS()
// {
//   setAllVerticesUnvisited();
//   for(int i = 0; i < vertices.size(); i++)
//   {
//     if(!vertices[i].visited)
//     DFTraversal(&vertices[i]);
//   }
// }

void Graph::setAllVerticesUnvisited()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
}

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

Graph::Graph()
{
  vector<vertex> vertices;
}

Graph::~Graph()
{
  while(!vertices.empty())
  {
    vertices.pop_back();
  }
}
