#include "Compile_Time_Options.h"
#include <vector>


class SW_Node;
class Cosmic_Node;

#pragma once
class SW_Node
{
 private:
  int MyID;
  int NNeighbors;
#ifdef CALCULATE_BETWEENESS
  double betweeness;
#endif

#ifdef WATTS_STROGATZ
  int NImmediateNeighbors;
  std::vector<SW_Node *> ImmediateNeighbors;
#endif
  std::vector<SW_Node *> Neighbors;
  
 public:

  // The constructor
  SW_Node(int ID); //std::vector<SW_Node*> Neighbors);

#ifdef CALCULATE_BETWEENESS
  void AddToBetweeness(double val){betweeness += val;}
  void SetBetweeness(double val){betweeness = val;}
  double GetBetweeness(){return betweeness;}
#endif

  // Simply return ID
  int ID(){return MyID;}

  // Return vector of pointers to neighbor nodes
  std::vector<SW_Node *> GetNeighbors(){return Neighbors;}

  // Sets a new ID.  Unlikely to need this.
  void SetID(int id){MyID = id;}

  // Sets a new neighbor list

  void SetNeighbors(std::vector<SW_Node *> &NewNeighborList);
  // Adds a pointer to a new neighbor to the neighbor list                                                          
  int AddNeighbor(SW_Node * NewNeighbor);

#ifdef WATTS_STROGATZ
  // Initialize immediate neighbor
  void SetNewImmediateNeighbors(std::vector<SW_Node *> &nodelist);
  // Adds immediate neighbor
  int AddImmediateNeighbor(SW_Node * NewNeighbor);
  // Pops back from the immediate neighbor list, and removes this edge
  int RemoveImmediateNeighbor(  std::vector<std::vector<int> > &Edges);
#endif

};


#pragma once
class Cosmic_Node
{
 private:
  int MyID;
  int NNeighbors;
  double x;
  double y;
  double z;
  double NFW_M;
  double NFW_SCALE;
  double NFW_C;
  std::vector<Cosmic_Node *> Neighbors;
#ifdef CALCULATE_BETWEENESS
  double betweeness;
#endif
 public:
  // The Constructor
  Cosmic_Node(int id, double X, double Y, double Z, double M, double A, double C);

  // Get NNeighbors

  int GetNeighborCount(){return NNeighbors;}
  
  // Get ID

  int ID(){return MyID;}

  // Get x
  double GetX(){return x;}
 
  // Get y
  double GetY(){return y;}

  // Get z
  double GetZ(){return z;}

  // Get m
  double GetM(){return NFW_M;}

  // Get a
  double GetA(){return NFW_SCALE;}

  // Get c
  double GetC(){return NFW_C;}
  
  // Gets neighbor vector
  std::vector<Cosmic_Node *> GetNeighbors(){return Neighbors;}

  // Returns the potential contribution at pos from this substructure
  double PotentialFromNodeAt(std::vector<double> &pos); 

  // Sets a new ID.  Unlikely to need this.  
  void SetID(int id){MyID = id;}

  // Adds a pointer to a new neighbor to the neighbor list 
  int AddNeighbor(Cosmic_Node * NewNeighbor);

#ifdef CALCULATE_BETWEENESS
  void AddToBetweeness(double val){betweeness += val;}
  void SetBetweeness(double val){betweeness = val;}
  double GetBetweeness(){return betweeness;}
#endif


};
