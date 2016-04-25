#include "Node.h"
#include <vector>


#pragma once
class Cosmic_Graph
{
 private:
  int NNodes;
  int NEdges;

  std::vector<std::vector<int> > EdgeList;
  std::vector<Cosmic_Node *> NodeList;

 public:
  // Constructor
  Cosmic_Graph();

  // Returns the "length" of the graph
  int GetNodeCount(){return NNodes;}

  int GetEdgeCount(){return NEdges;}

  // Returns the list of pointers to the nodes   
  std::vector<Cosmic_Node *>  GetNodes(){return NodeList;};

  // Returns the list of edges    
  std::vector<std::vector<int> > GetEdges(){return EdgeList;}

  // Gets the pointer to one node.   
  Cosmic_Node * GetNode(int MyID);

  // Adds a pointer to a new node to NodeList; returns 0 on success
  int AddNode(Cosmic_Node * NewNode);

  // Returns 1 if the node with ID NodeID is in the graph, else 0   
  int HasNode(int NodeID);

  // Adds an edge (2-element vector) to the Edgelist, returns 0 on success  
  int AddEdge(int Node1, int Node2);

};

#pragma once
class SW_Graph
{
 private:
  int NNodes;
  int NEdges;
  /*
    The edge list specifies links between pairs of IDs,
    which in general do not have to be the ordering of
    the node list.
  */
  std::vector<std::vector<int> > EdgeList;
  std::vector<SW_Node *> NodeList;

 public:
  // The constructor (mandatory, declares empty graph)
  SW_Graph();

  // Returns the "length" of the graph
  int GetNodeCount(){return NNodes;}

  int GetEdgeCount(){return NEdges;}

  void SetEdgeCount(int count){NEdges = count;}

  // Returns the list of pointers to the nodes
  std::vector<SW_Node *>  GetNodes(){return NodeList;};

  // Returns the list of edges
  std::vector<std::vector<int> > GetEdges(){return EdgeList;}

  // Sets edgelist to new list        

  void SetEdges(  std::vector<std::vector<int> > &Edges){EdgeList = Edges;}

  // Gets the pointer to one node.
  SW_Node * GetNode(int MyID);

  // Adds a pointer to a new node to NodeList; returns 0 on success
  int AddNode(SW_Node * NewNode);

  // Returns 1 if the node with ID NodeID is in the graph, else 0
  int HasNode(int NodeID);

  // Adds an edge (2-element vector) to the Edgelist, returns 0 on success
  int AddEdge(int Node1, int Node2);

};
