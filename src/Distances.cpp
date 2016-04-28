#include "../include/Proto.h"
#include "../include/Node.h"
#include "../include/Graph.h"
#include "../include/Compile_Time_Options.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <omp.h>


#ifdef COSMIC_WEB

void globalfns::Cosmic_GetAllPaths(Cosmic_Graph * graph)
{
  unsigned int i,j;
  int count;
  FILE * fileout;
#ifdef CALCULATE_BETWEENESS
  double betweeness_out;
#endif

  fileout = fopen("OUTPUTS/cosmic_distances.bin","wb");
  count = graph->GetNodeCount();
  fwrite(&count, sizeof(int), 1, fileout);


  std::cout << "Getting distances and betweeness..." << std::endl;
#ifdef OPENMP // Need to fix race condition for file writing  
#pragma omp parallel for
#endif
  for (j=0; j < count; j++)
    {
      /*
	Get all paths
      */
      std::vector<int> distances(count, -1);
      globalfns::Cosmic_PathLengthsFromNode(graph->GetNodes()[j], graph, distances);
#ifdef OPENMP
#pragma omp critical
#endif
      for ( i = 0; i < count; i++ )
        {
	  /*
	    Write and reset distances
	  */
          fwrite(&distances[i], sizeof(int), 1, fileout);
          distances[i] = -1;
        }
    }
  fclose(fileout);
#ifdef CALCULATE_BETWEENESS
  fileout = fopen("OUTPUTS/cosmic_betweeness.bin","wb");
  for (i=0; i<count; i++)
    {
      betweeness_out = graph->GetNodes()[i]->GetBetweeness();
      
      /*
	Write betweenesses
      */
      fwrite(&betweeness_out, sizeof(double), 1, fileout);
    }
  fclose(fileout);
#endif
}


void globalfns::Cosmic_PathLengthsFromNode(Cosmic_Node * node, Cosmic_Graph * graph, std::vector<int>  &distances)
{
  unsigned int i;
  unsigned int j;
  unsigned int level;
#ifdef CALCULATE_BETWEENESS
  double sigma_ratio;
  Cosmic_Node * ThisNode;
  std::vector<int> sigma(graph->GetNodeCount(), 0);
  std::vector<double> delta(graph->GetNodeCount(),0.);
#endif // CALCULATE_BETWEENESS

  std::vector<Cosmic_Node *> NextShell;
  std::vector<Cosmic_Node *> CurrentShell;
  std::vector<Cosmic_Node *> MyNeighbors;
#ifdef CALCULATE_BETWEENESS
  std::vector<Cosmic_Node *> BetweenessShell;
  std::vector<Cosmic_Node *> Predecessors;
  sigma[node->ID()] = 1;
#endif // CALCULATE_BETWEENESS

  level = 0;
  distances[node->ID()]=0;
  CurrentShell.push_back(node);

  while (CurrentShell.size() != 0)
    {
      NextShell.clear(); // Empties vector
      for (i=0; i < CurrentShell.size(); i++)
        {
#ifdef CALCULATE_BETWEENESS
          BetweenessShell.push_back(CurrentShell[i]);
#endif
          MyNeighbors = CurrentShell[i]->GetNeighbors();                  
          for (j=0; j < MyNeighbors.size(); j++)
            {
              if (distances[MyNeighbors[j]->ID()] == -1)
                {
                  NextShell.push_back(MyNeighbors[j]);
                  distances[MyNeighbors[j]->ID()] = level + 1;
                }
#ifdef CALCULATE_BETWEENESS
              if (distances[MyNeighbors[j]->ID()] == distances[CurrentShell[i]->ID()] + 1)
                {
		  /*
		    Compute dependencies
		  */
                  sigma[MyNeighbors[j]->ID()] += sigma[CurrentShell[i]->ID()];
                  Predecessors.push_back(CurrentShell[i]);
		}
#endif // CALCULATE_BETWEENESS
            }
        }
      
      CurrentShell.clear();
      for (i=0; i < NextShell.size(); i++)
        {
          CurrentShell.push_back(NextShell[i]);
        }
      level++;
    }

#ifdef CALCULATE_BETWEENESS
  
  i = BetweenessShell.size() - 1;
  while (BetweenessShell.size() != 0)
    {
      ThisNode = BetweenessShell[i]; // ThisNode is Brande's node w 
      BetweenessShell.pop_back();

      for (j=0; j < Predecessors.size(); j++)
        {
	  /*
	    The predecessor node is Brande's v  
	  */
          if (Predecessors[j]->ID() != ThisNode->ID() && Predecessors[j]->ID() != node->ID() && distances[Predecessors[j]->ID()] != -1)
            {
              sigma_ratio = ((double)sigma[Predecessors[j]->ID()] / (double)sigma[ThisNode->ID()] );
              delta[Predecessors[j]->ID()] += sigma_ratio * (1. + (double)delta[ThisNode->ID()]);
            }
	  else if (distances[Predecessors[j]->ID()] == -1)
	    {
	      delta[Predecessors[j]->ID()] += 0.;
	    }
          else
            {
              delta[Predecessors[j]->ID()] = 1;
            }
	}
      if (node->ID() != ThisNode->ID())
        {
          ThisNode->AddToBetweeness( delta[ThisNode->ID()]);
        }

      i--; // pop back index
    }
#endif

}
#endif // COSMIC_WEB



#ifdef RANDOM_SMALL_WORLD

/*
  Do N BFS on the graph to get distance vectors and write them to hard disk
*/

void globalfns::SW_GetAllPaths(SW_Graph * graph)//, std::vector<int> &distances)
{
  unsigned int i,j;
  int count;
  FILE * fileout;
#ifdef CALCULATE_BETWEENESS
  double betweeness_out;
#endif

  fileout = fopen("OUTPUTS/sw_distances.bin","wb");
  count = NODES;
  fwrite(&count, sizeof(int), 1, fileout);
  //std::vector<int> distances(count, -1);

#ifdef OPENMP // Need to fix race condition for file writing
#pragma omp parallel for 
#endif
  for (j=0; j < NODES; j++)
    {
      std::vector<int> distances(count, -1);
      globalfns::SW_PathLengthsFromNode(graph->GetNodes()[j], graph, distances);
#ifdef OPENMP
#pragma omp critical
#endif
      for ( i = 0; i < NODES; i++ )
        {
	  /*
	    Write and update distances
	  */
	  fwrite(&distances[i], sizeof(int), 1, fileout);
          distances[i] = -1;
        }
    }
  fclose(fileout);
#ifdef CALCULATE_BETWEENESS
  fileout = fopen("OUTPUTS/sw_betweeness.bin","wb");
  for (i=0; i<NODES; i++)
    {
      betweeness_out = graph->GetNodes()[i]->GetBetweeness();
      /*
	Write betweenesses
      */
      fwrite(&betweeness_out, sizeof(double), 1, fileout);
    }
  fclose(fileout);
#endif
}

/*
  Do a BFS on the graph
*/

void globalfns::SW_PathLengthsFromNode(SW_Node * node, SW_Graph * graph, std::vector<int>  &distances)
{
  unsigned int i;
  unsigned int j;
  unsigned int level;
#ifdef CALCULATE_BETWEENESS
  double sigma_ratio;
  SW_Node * ThisNode;
  std::vector<int> sigma(NODES, 0);
  std::vector<double> delta(NODES,0.);
#endif

  std::vector<SW_Node *> NextShell;
  std::vector<SW_Node *> CurrentShell;
  std::vector<SW_Node *> MyNeighbors;
#ifdef CALCULATE_BETWEENESS
  std::vector<SW_Node *> BetweenessShell;
  std::vector<SW_Node *> Predecessors;
  sigma[node->ID()] = 1;
#endif

  level = 0;
  distances[node->ID()]=0;
  CurrentShell.push_back(node);

  while (CurrentShell.size() != 0)
    {
      NextShell.clear(); // Empties vector
      
      for (i=0; i < CurrentShell.size(); i++)
	{
#ifdef CALCULATE_BETWEENESS
	  BetweenessShell.push_back(CurrentShell[i]);
#endif
	  MyNeighbors = CurrentShell[i]->GetNeighbors();
	  for (j=0; j < MyNeighbors.size(); j++)
	    {
	      if (distances[MyNeighbors[j]->ID()] == -1)
		{
		  NextShell.push_back(MyNeighbors[j]);
		  distances[MyNeighbors[j]->ID()] = level + 1;
		}
#ifdef CALCULATE_BETWEENESS
	      if (distances[MyNeighbors[j]->ID()] == distances[CurrentShell[i]->ID()] + 1)
		{
		  sigma[MyNeighbors[j]->ID()] += sigma[CurrentShell[i]->ID()];
		  Predecessors.push_back(CurrentShell[i]);
		}
#endif
	    }
	}

      CurrentShell.clear();
      for (i=0; i < NextShell.size(); i++)
	{
	  CurrentShell.push_back(NextShell[i]);
	}
      level++;
    }

#ifdef CALCULATE_BETWEENESS

  i = BetweenessShell.size() - 1;
  while (BetweenessShell.size() != 0)
    {
      ThisNode = BetweenessShell[i]; // ThisNode is Brande's node w
      BetweenessShell.pop_back(); 

      for (j=0; j < Predecessors.size(); j++)
	{
	  /*
	    The predecessor node is Brande's v
	  */
	  if (Predecessors[j]->ID() != ThisNode->ID() && Predecessors[j]->ID() != node->ID())
	    {
	      sigma_ratio = ((double)sigma[Predecessors[j]->ID()] / (double)sigma[ThisNode->ID()] );
	      delta[Predecessors[j]->ID()] += sigma_ratio * (1. + (double)delta[ThisNode->ID()]);
	    }
	  else
	    {
	      delta[Predecessors[j]->ID()] = sigma[Predecessors[j]->ID()];
	    }
	}
      if (node->ID() != ThisNode->ID())
	{
	  ThisNode->AddToBetweeness( delta[ThisNode->ID()]);
	}

      i--;
    }
#endif
}

#endif // RANDOM_SMALL_WORLD
