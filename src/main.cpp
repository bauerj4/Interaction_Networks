#include "../include/Node.h"
#include "../include/Graph.h"
#include "../include/Proto.h"
#include "../include/Compile_Time_Options.h"
#include <iostream>

int main(int argc, char ** argv)
{

#ifdef COSMIC_WEB
  Cosmic_Graph * graph = new Cosmic_Graph();
  globalfns::Cosmic_Init(graph, argv[1]);
  globalfns::Cosmic_GetAllPaths(graph);
#endif


#ifdef RANDOM_SMALL_WORLD
  SW_Graph * graph = new SW_Graph();
  std::cout << "Initializing SW Graph..." << std::endl;
  globalfns::SW_Init(graph);
  std::cout << "Initialized graph. Doing calculations." << std::endl;
  globalfns::SW_GetAllPaths(graph);
  std::cout << "Calculations completed. Finalizing..." << std::endl;
#endif


#ifdef COSMIC_WEB
  globalfns::Cosmic_Finalize(graph);
#endif

#ifdef RANDOM_SMALL_WORLD
  globalfns::SW_Finalize(graph);
#endif


  return 0;
}
