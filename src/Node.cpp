#include "../include/Node.h"
#include "../include/Graph.h"
#include "../include/Compile_Time_Options.h"
#include <iostream>

SW_Node::SW_Node(int MyID)//, std::vector<SW_Node *> MyNeighbors)
{
  SetID(MyID);
#ifdef CALCULATE_BETWEENESS
  SetBetweeness(1.);
#endif
}


// Adds a pointer to a new neighbor to the neighbor list                 
int SW_Node::AddNeighbor(SW_Node * NewNeighbor)
{
  Neighbors.push_back(NewNeighbor);
  NNeighbors++;
  return 0;
}

void SW_Node::SetNeighbors(std::vector<SW_Node *> &NewNeighborList)
{
  Neighbors = NewNeighborList; // Sets addresses equal
  NNeighbors = NewNeighborList.size();
}

#ifdef WATTS_STROGATZ

void SW_Node::SetNewImmediateNeighbors(std::vector<SW_Node *> &nodelist)
{
  int i;
  for (i=0; i < nodelist.size(); i++)
    {
      AddImmediateNeighbor(nodelist[i]);
    }
}


int SW_Node::AddImmediateNeighbor(SW_Node * NewNeighbor)
{
  ImmediateNeighbors.push_back(NewNeighbor);
  NImmediateNeighbors++;
  return 0;
}

int SW_Node::RemoveImmediateNeighbor(  std::vector<std::vector<int> > &Edges)
{
  SW_Node * last_node;
  std::vector<SW_Node *> last_nodelist;
  int ThisID, LastID, i, ThisIdx, edge1, edge2;

  ThisIdx = -1;
  ThisID = MyID;
  last_node = ImmediateNeighbors[ImmediateNeighbors.size() - 1];
  LastID = last_node->ID();
  
  edge1 = -1;
  edge2 = -1;
  for (i=0; i < Edges.size(); i++)
    {
      if (Edges[i][0] == ThisID && Edges[i][1] == LastID)
	{
	  edge1 = i;
	}
     
      
      else if(Edges[i][0] == LastID && Edges[i][1] == ThisID)
	{
	  edge2 = i;
	}
    }
  if (edge1 != -1)
    Edges.erase(Edges.begin() + edge1);
  
  if (edge2 != -1)
    Edges.erase(Edges.begin() + edge2);
  


  last_nodelist = last_node->GetNeighbors();
  // Get index of this node in neighbor list

  for (i=0; i < last_nodelist.size(); i++)
    {
      if (last_nodelist[i]->ID() == ThisID)
	ThisIdx = i;
    }

  // Only remove a neighbor if we can
  if (ThisIdx != -1)
    {
      last_nodelist.erase(last_nodelist.begin() + ThisIdx);
      last_node->SetNeighbors(last_nodelist);

      ImmediateNeighbors.pop_back();

      NImmediateNeighbors--;
      NNeighbors--;
    }
  return 0;
}

#endif

Cosmic_Node::Cosmic_Node(int id, double X, double Y, double Z, double M, double A, double C)
{
  NNeighbors=0;
  MyID = id;
  x = X;
  y = Y;
  z = Z;
  NFW_M = M;
  NFW_SCALE = A;
  NFW_C = C;
}

// Adds a pointer to a new neighbor to the neighbor list  
int Cosmic_Node::AddNeighbor(Cosmic_Node * NewNeighbor)
{
  Neighbors.push_back(NewNeighbor);
  NNeighbors++;
  return 0;
}
