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
void Graph::simulateFire()
{
  for(int j = 0; vertices.size(); j++)
  {
    if(vertices[j].isGone)
    {
      return;
    }

    if(!vertices[j].onFire)
    {
      int chance = 0;
      for(int i = 0; vertices[j].Edges.size(); i++)
      {
        chance += vertices[j].Edges[i].v->severity;
      }
      chance += fuel;
      int random = rand() % 30 + 1;
      if(chance >= random)
      {
        vertices[j].onFire = true;
        vertices[j].severity = 1;
        return;
      }
    }
    else
    {
      int random = rand() % 10 + 1;
      int chance = random + vertices[j].fuel;
      if(chance >= 10)
      {
        if(vertices[j].severity == 10)
        {
          vertices[j].isGone = true;
          vertices[j].severity = 0;
          vertices[j].onFire = false;
        }
        else
        {
          vertices[j].severity++;
        }
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

int main(int argc, char const *argv[])
{
  Graph landMap;
  Graph skyMap;

  landMap.addVertex(Rothstown, 3, 150);
  landMap.addVertex(BoizTrailerPark, 3, 48);
  landMap.addVertex(Fancytown, 3, 13);
  landMap.addVertex(IndustrialZone, 4, 75);
  landMap.addVertex(WestForest, 5, 2);
  landMap.addVertex(SouthForest, 5, 0);
  landMap.addVertex(EastForest, 5, 3);
  landMap.addVertex(Mountains, 1, 1);
  landMap.addVertex(Southtown, 3, 89);

  skyMap.addVertex(Rothstown, 3, 150);
  skyMap.addVertex(BoizTrailerPark, 3, 48);
  skyMap.addVertex(Fancytown, 3, 13);
  skyMap.addVertex(Industrial, 4, 75);
  skyMap.addVertex(WestForest, 5, 2);
  skyMap.addVertex(SouthForest, 5, 0);
  skyMap.addVertex(EastForest, 5, 3);
  skyMap.addVertex(Mountains, 1, 1);
  skyMap.addVertex(Southtown, 3, 89);

  landMap.addEdge(Rothstown, BoizTrailerPark, 5);
  landMap.addEdge(Rothstown, Fancytown, 5);
  landMap.addEdge(Rothstown, IndustrialZone, 7);

  landMap.addEdge(BoizTrailerPark, Rothstown, 5);
  landMap.addEdge(BoizTrailerPark, WestForest, 5);
  landMap.addEdge(BoizTrailerPark, IndustrialZone, 5);
  landMap.addEdge(BoizTrailerPark, Fancytown, 7);
  landMap.addEdge(BoizTrailerPark, SouthForest, 7);

  landMap.addEdge(WestForest, SouthForest, 5);
  landMap.addEdge(WestForest, BoizTrailerPark, 5);
  landMap.addEdge(WestForest, IndustrialZone, 7);

  landMap.addEdge(Fancytown, Rothstown, 5);
  landMap.addEdge(Fancytown, IndustrialZone, 5);
  landMap.addEdge(Fancytown, Mountains, 5);
  landMap.addEdge(Fancytown, BoizTrailerPark, 7);
  landMap.addEdge(Fancytown, EastForest, 7);

  landMap.addEdge(IndustrialZone, Fancytown, 5);
  landMap.addEdge(IndustrialZone, BoizTrailerPark, 5);
  landMap.addEdge(IndustrialZone, EastForest, 5);
  landMap.addEdge(IndustrialZone, SouthForest, 5);
  landMap.addEdge(IndustrialZone, Rothstown, 7);
  landMap.addEdge(IndustrialZone, WestForest, 7);
  landMap.addEdge(IndustrialZone, Southtown, 7);
  landMap.addEdge(IndustrialZone, Mountains, 7);

  landMap.addEdge(SouthForest, WestForest, 5);
  landMap.addEdge(SouthForest, IndustrialZone, 5);
  landMap.addEdge(SouthForest, Southtown, 5);
  landMap.addEdge(SouthForest, BoizTrailerPark, 7);
  landMap.addEdge(SouthForest, EastForest, 7);

  landMap.addEdge(Mountains, Fancytown, 5);
  landMap.addEdge(Mountains, IndustrialZone, 7);
  landMap.addEdge(Mountains, EastForest, 5);

  landMap.addEdge(EastForest, Mountians, 5);
  landMap.addEdge(EastForest, IndustrialZone, 5);
  landMap.addEdge(EastForest, Southtown, 5);
  landMap.addEdge(EastForest, Fancytown, 7);
  landMap.addEdge(EastForest, SouthForest, 7);

  landMap.addEdge(Southtown, EastForest, 5);
  landMap.addEdge(Southtown, SouthForest, 5);
  landMap.addEdge(Southtown, IndustrialZone, 7);




  skyMap.addEdge(Rothstown, BoizTrailerPark, 5);
  skyMap.addEdge(Rothstown, Fancytown, 5);
  skyMap.addEdge(Rothstown, IndustrialZone, 7);
  skyMap.addEdge(Rothstown, WestForest, 10);
  skyMap.addEdge(Rothstown, SouthForest, 11);
  skyMap.addEdge(Rothstown, Mountains, 10);
  skyMap.addEdge(Rothstown, EastForest, 11);
  skyMap.addEdge(Rothstown, Southtown, 14);

  skyMap.addEdge(BoizTrailerPark, Rothstown, 5);
  skyMap.addEdge(BoizTrailerPark, WestForest, 5);
  skyMap.addEdge(BoizTrailerPark, IndustrialZone, 5);
  skyMap.addEdge(BoizTrailerPark, Fancytown, 7);
  skyMap.addEdge(BoizTrailerPark, SouthForest, 7);
  skyMap.addEdge(BoizTrailerPark, Mountains, 11);
  skyMap.addEdge(BoizTrailerPark, EastForest, 10);
  skyMap.addEdge(BoizTrailerPark, Southtown, 11);

  skyMap.addEdge(WestForest, SouthForest, 5);
  skyMap.addEdge(WestForest, BoizTrailerPark, 5);
  skyMap.addEdge(WestForest, IndustrialZone, 7);
  skyMap.addEdge(WestForest, Rothstown, 10);
  skyMap.addEdge(WestForest, Fancytown, 11);
  skyMap.addEdge(WestForest, Mountains, 14);
  skyMap.addEdge(WestForest, EastForest, 11);
  skyMap.addEdge(WestForest, Southtown, 10);

  skyMap.addEdge(Fancytown, Rothstown, 5);
  skyMap.addEdge(Fancytown, IndustrialZone, 5);
  skyMap.addEdge(Fancytown, Mountains, 5);
  skyMap.addEdge(Fancytown, BoizTrailerPark, 7);
  skyMap.addEdge(Fancytown, EastForest, 7);
  skyMap.addEdge(Fancytown, SouthForest, 10);
  skyMap.addEdge(Fancytown, Southtown, 11);
  skyMap.addEdge(Fancytown, WestForest, 11);

  skyMap.addEdge(IndustrialZone, Fancytown, 5);
  skyMap.addEdge(IndustrialZone, BoizTrailerPark, 5);
  skyMap.addEdge(IndustrialZone, EastForest, 5);
  skyMap.addEdge(IndustrialZone, SouthForest, 5);
  skyMap.addEdge(IndustrialZone, Rothstown, 7);
  skyMap.addEdge(IndustrialZone, WestForest, 7);
  skyMap.addEdge(IndustrialZone, Southtown, 7);
  skyMap.addEdge(IndustrialZone, Mountains, 7);

  skyMap.addEdge(SouthForest, WestForest, 5);
  skyMap.addEdge(SouthForest, IndustrialZone, 5);
  skyMap.addEdge(SouthForest, Southtown, 5);
  skyMap.addEdge(SouthForest, BoizTrailerPark, 7);
  skyMap.addEdge(SouthForest, EastForest, 7);
  skyMap.addEdge(SouthForest, Rothstown, 11);
  skyMap.addEdge(SouthForest, Fancytown, 10);
  skyMap.addEdge(SouthForest, Mountains, 11);

  skyMap.addEdge(Mountains, Fancytown, 5);
  skyMap.addEdge(Mountains, IndustrialZone, 7);
  skyMap.addEdge(Mountains, EastForest, 5);
  skyMap.addEdge(Mountains, Rothstown, 10);
  skyMap.addEdge(Mountains, Southtown, 10);
  skyMap.addEdge(Mountains, WestForest, 14);
  skyMap.addEdge(Mountains, SouthForest, 11);
  skyMap.addEdge(Mountains, BoizTrailerPark, 11);

  skyMap.addEdge(EastForest, Mountians, 5);
  skyMap.addEdge(EastForest, IndustrialZone, 5);
  skyMap.addEdge(EastForest, Southtown, 5);
  skyMap.addEdge(EastForest, Fancytown, 7);
  skyMap.addEdge(EastForest, SouthForest, 7);
  skyMap.addEdge(EastForest, Rothstown, 11);
  skyMap.addEdge(EastForest, BoizTrailerPark, 10);
  skyMap.addEdge(EastForest, WestForest, 11);

  skyMap.addEdge(Southtown, EastForest, 5);
  skyMap.addEdge(Southtown, SouthForest, 5);
  skyMap.addEdge(Southtown, IndustrialZone, 7);
  skyMap.addEdge(Southtown, WestForest, 10);
  skyMap.addEdge(Southtown, Mountains, 10);
  skyMap.addEdge(Southtown, BoizTrailerPark, 11);
  skyMap.addEdge(Southtown, Fancytown, 11);
  skyMap.addEdge(Southtown, Rothstown, 14);

  skyMap.movePilot(Rothstown);
  landMap.vertices[0].onFire = true;
  landMap.vertices[0].severity = 5;

  while(1)
  {
    string choice;
    landMap.simulateFire();
    //PriorityQueue
    cin >> choice;
    landMap.movePilot(choice);
    landMap.fightFire();
  
  }
  return 0;
}
