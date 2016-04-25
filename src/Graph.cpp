#include "../include/Node.h"
#include "../include/Graph.h"
#include <vector>
#include <iostream>


Cosmic_Graph::Cosmic_Graph()
{
  NNodes=0;
  NEdges=0;
}

int Cosmic_Graph::AddNode(Cosmic_Node * NewNode)
{
  NodeList.push_back(NewNode);
  NNodes++;
  return 0; // Success    
}

int Cosmic_Graph::HasNode(int NodeID)
{
  unsigned int i;
  bool InList = false;

  for (i=0; i < NodeList.size(); i++)
    {
      if ((NodeList[i])->ID() == NodeID)
        {
          InList = true;
        }
    }
  if (InList)
    return 1; // Found      
  else
    return 0; // Not Found   
}


Cosmic_Node * Cosmic_Graph::GetNode(int NodeID)
{
  unsigned int i;
  Cosmic_Node * ThisNode = NULL;

  for (i=0; i < NodeList.size(); i++)
    {
      if ((NodeList[i])->ID() == NodeID)
        {
          ThisNode = NodeList[i];
	}
    }

  return ThisNode; // NULL if not found, we probably should handle this   
}


int Cosmic_Graph::AddEdge(int Node1_ID, int Node2_ID)
{
  Cosmic_Node * Node1;
  Cosmic_Node * Node2;

  int ThisEdge[2] = {Node1_ID, Node2_ID};
  std::vector<int> Edge(ThisEdge, ThisEdge + sizeof(ThisEdge)/sizeof(int));
  EdgeList.push_back(Edge);
  NEdges++;

  Node1 = GetNode(Node1_ID);
  Node2 = GetNode(Node2_ID);
  Node1->AddNeighbor(Node2);
  Node2->AddNeighbor(Node1);

  return 0; // Success  
}





SW_Graph::SW_Graph()
{
  NNodes=0;
  NEdges=0;
}


int SW_Graph::AddNode(SW_Node * NewNode)
{
  NodeList.push_back(NewNode);
  NNodes++;
  return 0; // Success
}


int SW_Graph::HasNode(int NodeID)
{
  unsigned int i;
  bool InList = false;


  for (i=0; i < NodeList.size(); i++)
    {
      if ((NodeList[i])->ID() == NodeID)
	{
	  InList = true;
	}
    }
  if (InList)
    return 1; // Found
  else
    return 0; // Not Found
}

SW_Node * SW_Graph::GetNode(int NodeID)
{
  unsigned int i;
  SW_Node * ThisNode = NULL;

  for (i=0; i < NodeList.size(); i++)
    {
      if ((NodeList[i])->ID() == NodeID)
        {
	  ThisNode = NodeList[i];
        }
    }

  return ThisNode; // NULL if not found, we probably should handle this
}

int SW_Graph::AddEdge(int Node1_ID, int Node2_ID)
{
  SW_Node * Node1;
  SW_Node * Node2;

  int ThisEdge[2] = {Node1_ID, Node2_ID};
  std::vector<int> Edge(ThisEdge, ThisEdge + sizeof(ThisEdge)/sizeof(int));
  EdgeList.push_back(Edge);
  NEdges++;

  Node1 = GetNode(Node1_ID);
  Node2 = GetNode(Node2_ID);
  Node1->AddNeighbor(Node2);
  Node2->AddNeighbor(Node1);

  return 0; // Success
}
