#include "../include/Proto.h"
#include "../include/Node.h"
#include "../include/Graph.h"
#include "../include/Compile_Time_Options.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <omp.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>


#ifdef COSMIC_WEB
void globalfns::Cosmic_Init(Cosmic_Graph * graph, char * filename)
{
  globalfns::Cosmic_GenerateHalos(graph, filename);
  globalfns::Cosmic_FindInteractions(graph);
}


void globalfns::Cosmic_FindInteractions(Cosmic_Graph * graph)
{
  int i,j,k;
  int num = graph->GetNodeCount();
  double ThisPot;
  bool AlreadyNeighbor = false;
  std::vector<Cosmic_Node *> nodelist = graph->GetNodes();
  std::vector<Cosmic_Node *> MyNeighbors;
  // Sum over all interactions

#ifdef USE_KEPLER
  std::cout << "Ignoring overlapping halos.  Kepler potential selected." << std::endl;
#endif // USE_KEPLER

  std::cout << "Computing interactions for " << num << " particles." << std::endl; 
  std::cout << "Adding interaction edges bases on specified criteria: " << std::endl;
  std::cout << "ANDROMEDA_POTENTIAL = " << ANDROMEDA_POTENTIAL << std::endl;
  std::cout << "THRESHOLD_FRACTION  = " << THRESHOLD_FRACTION << std::endl;
#ifdef OPENMP
#pragma omp parallel for private(MyNeighbors,j)
#endif // OPENMP
  for (i=0; i < num; i++)
    {
      //#pragma omp critical 
      //std::cout << "Computing interaction " << i << "/" << num << std::endl;
      MyNeighbors = nodelist[i]->GetNeighbors();

      for (j=0; j < num; j++)
	{
	  if (i != j)
	    {
#ifdef USE_KEPLER
	      for (k=0; k < MyNeighbors.size(); k++)
		{
		  if (MyNeighbors[k]->ID() == nodelist[j]->ID())
		    AlreadyNeighbor=true;	      
		}  
	      if (!AlreadyNeighbor)
		{
		  ThisPot = Cosmic_Kepler(graph, nodelist[i]->ID(), nodelist[j]->ID());
		  //		  std::cout << ThisPot << std::endl;
		  
#pragma omp critical
		  if (ThisPot < THRESHOLD_FRACTION * ANDROMEDA_POTENTIAL)
		    {
		      //std::cout << "Added edge." << std::endl;
		      graph->AddEdge(nodelist[i]->ID(),nodelist[j]->ID());
		    }
		}
#endif // USE_KEPLER
	      
	      AlreadyNeighbor=false;
	    }
	}
      //std::cout << "Finished checking for interactions on body " << nodelist[i]->ID() << std::endl;
    }
  
  std::cout << "Generated cosmic web with " << graph->GetEdgeCount() << " edges." << std::endl;
}

void globalfns::Cosmic_GenerateHalos(Cosmic_Graph * graph, char * filename)
{
  // Use cpp to read, better tokenizing functions
  std::ifstream in_stream;
  std::string line;
  int newID = 0;
  in_stream.open(filename);

  std::cout << "Reading halo data..." << std::endl;
  
  while(!in_stream.eof())
    {
      //in_stream >> line;
      std::getline(in_stream, line);
      if (line.size() == 0 || line[0] =='#')
	{
	  // Do nothing
	}

      else
	{
	  std::stringstream ss(line);
	  std::string item;
	  char delim = ' ';
	  int i;
	  std::vector<std::string> tokens;
	  Cosmic_Node * NewNode;
	  double newX, newY, newZ, newM, newA, newC;
	  // Use old rockstar format
	  while (std::getline(ss,item,delim ))
	    tokens.push_back(item);


	  newM = atof(tokens[2].c_str()); // solar masses / h
	  newX = 1.e3 * atof(tokens[8].c_str()); // kpc / h (comoving)
	  newY = 1.e3 * atof(tokens[9].c_str()); // kpc / h (comoving)
	  newZ = 1.e3 * atof(tokens[10].c_str()); // kpc / h (comoving)
	  newC = atof(tokens[7].c_str()) / atof(tokens[8].c_str()); // NFW concentration parameter
	  newA = atof(tokens[8].c_str()); // NFW scale radius

	  if (newM > MASS_FILTER)
	    {
	      NewNode = new Cosmic_Node(newID, newX, newY, newZ, newM, newA, newC);
	      graph->AddNode(NewNode);
	      newID++;
	    }
	}
      //newID++;
    }

  std::cout << "Added " << graph->GetNodeCount() << " nodes to the cosmic web." << std::endl;
  in_stream.close();
}

#endif // COSMIC_WEB

#ifdef RANDOM_SMALL_WORLD
void globalfns::SW_Init(SW_Graph * graph)
{
  srand(SEED);
  SW_GenerateBase(graph);
  SW_GenerateRandomEdges(graph);
}


void globalfns::SW_GenerateBase(SW_Graph * graph)
{
  unsigned int i,j;
  SW_Node * NewNode;

  std::vector<int> edge(2,-1);

#ifdef WATTS_STROGATZ
  std::vector<SW_Node *> neighborlist;
  SW_Node * thisnode;
#endif

  /*
    Add nodes.
  */
  
  std::cout << "Adding small world nodes..." << std::endl;
  for (i=0; i < NODES; i++)
    {
      NewNode = new SW_Node(i);
      graph->AddNode(NewNode);
    }
  std::cout << "Added " << i << " new small world nodes." << std::endl;

  /*
    Add short edges
  */
  std::cout << "Adding short edges..." << std::endl;

  for (i=0; i < NODES; i++)
    {
      for (j=1; j <= Z_SHORT_EDGES/2; j++)
	{
	  graph->AddEdge(i % NODES,(i+j) % NODES);
	}
    } 
  std::cout << "Added " << graph->GetEdgeCount() << " new short edges.\n";

  /*
    Set the immediate neighbor list
  */

#ifdef WATTS_STROGATZ
  for (i=0; i < NODES; i++)
    {
      thisnode = graph->GetNode(i);
      neighborlist = thisnode->GetNeighbors();
      thisnode->SetNewImmediateNeighbors(neighborlist);
    }
#endif


}


void globalfns::SW_GenerateRandomEdges(SW_Graph * graph)
{
  unsigned int MAX;
  unsigned int i;
  std::vector<int> pair;
#ifdef WATTS_STROGATZ
  std::vector<std::vector<int> > Edges;
  SW_Node * thisnode;

  //Edges = graph->GetEdges();
#endif

  i=0;
  MAX = (int)floor(NODES * JUMP_FRACTION * Z_SHORT_EDGES/2);

  std::cout << "Adding random edges..." << std::endl;
  while (i < MAX)
    {
      pair = globalfns::SerialUnifPair(0,NODES-1);
      graph -> AddEdge(pair[0], pair[1]);

#ifdef WATTS_STROGATZ
      // Rewire
      Edges = graph->GetEdges();
      //std::cout << "Before removal, edgelist has " << graph->GetEdgeCount() << std::endl;
      thisnode = graph->GetNode(pair[0]);
      thisnode->RemoveImmediateNeighbor(Edges);
      graph->SetEdges(Edges);
      graph->SetEdgeCount(Edges.size());
      //std::cout << "Removed the neighbor edge. New edge count is " << Edges.size() << std::endl;
#endif
      i++;
    }

  std::cout << "Added " << MAX << " random edges." << std::endl;
  int edgecount = graph->GetEdgeCount();
  std::cout << edgecount << " total edges." << std::endl;
}
#endif //RANDOM_SMALL_WORLD
