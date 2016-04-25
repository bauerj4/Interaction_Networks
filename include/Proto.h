#include "Graph.h"
#include "Compile_Time_Options.h"
#include <vector>

namespace globalfns
{
  /*
    Startup
  */
  

#ifdef COSMIC_WEB
  void Cosmic_Init(Cosmic_Graph * graph, char * filename);
  void Cosmic_GenerateHalos(Cosmic_Graph * graph,char * filename);
#endif
  
#ifdef RANDOM_SMALL_WORLD
  void SW_Init(SW_Graph * graph);
  void SW_GenerateBase(SW_Graph * graph);
  void SW_GenerateRandomEdges(SW_Graph * graph);
#endif

  /*
    Stats
  */

  std::vector<int> SerialUnifPair(int a, int b);

  /*
    Distances
  */

#ifdef RANDOM_SMALL_WORLD
  void SW_GetAllPaths(SW_Graph * graph);//, std::vector<int> &distances);
  void SW_PathLengthsFromNode(SW_Node * node, SW_Graph * graph, std::vector<int>  &distances);
#endif 

#ifdef COSMIC_WEB
  void Cosmic_GetAllPaths(Cosmic_Graph * graph);
  void Cosmic_PathLengthsFromNode(Cosmic_Node * node, Cosmic_Graph * graph, std::vector<int>  &distances);
#endif

  /*
    Potentials
  */

#ifdef COSMIC_WEB
  double Cosmic_Kepler(Cosmic_Graph * graph, int NodeID_1, int NodeID_2);
  void Cosmic_FindInteractions(Cosmic_Graph * graph);
#endif


  /*
    Termination
  */

#ifdef RANDOM_SMALL_WORLD
  void SW_Finalize(SW_Graph * graph);
#endif

#ifdef COSMIC_WEB
  void Cosmic_Finalize(Cosmic_Graph * graph);
#endif
}
