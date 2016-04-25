#include "../include/Compile_Time_Options.h"
#include "../include/Proto.h"
#include "../include/Node.h"
#include "../include/Graph.h"
#include <fstream>
#include <stdio.h>
#include <iostream>

#ifdef COSMIC_WEB
void globalfns::Cosmic_Finalize(Cosmic_Graph * graph)
{
  unsigned int i = 0;
  int count = graph->GetNodeCount();
  Cosmic_Node * node1;
  Cosmic_Node * node2;
  double x1,y1,z1;
  double x2,y2,z2;
  FILE * fileout;

  std::cout << "Writing cosmic_vertices.bin..." << std::endl;

  fileout = fopen("./OUTPUTS/cosmic_vertices.bin","wb");
  std::vector<Cosmic_Node *> nodelist = graph->GetNodes();

  for (i=0; i<nodelist.size(); i++)
    {
      x1 = nodelist[i]->GetX();
      y1 = nodelist[i]->GetY();
      z1 = nodelist[i]->GetZ();
      double pos[3] = {x1,y1,z1};
      fwrite(pos, sizeof(double), 3, fileout);
    }

  fclose(fileout);

  fileout = fopen("./OUTPUTS/cosmic_edges.bin", "wb");
  std::vector<std::vector<int> > Edges = graph->GetEdges();

  std::cout << "Writing cosmic_edges.bin..." << std::endl;

  //fwrite(&count, sizeof(int), 1, fileout);
  for (i = 0; i < graph->GetEdgeCount(); i++)
    {
      node1 = graph->GetNode(Edges[i][0]);
      node2 = graph->GetNode(Edges[i][1]);

      x1 = node1->GetX();
      y1 = node1->GetY();
      z1 = node1->GetZ();
      
      x2 = node2->GetX();
      y2 = node2->GetY();
      z2 = node2->GetZ();

      //std::cout << "x1, y1, z1 = " << x1 << ',' << y1 << ',' << z1 << std::endl;
      //std::cout << "x2, y2, z2 = " << x2 << ',' << y2 << ',' << z2 << std::endl;

      double pos1[3] = {x1,y1,z1};
      double pos2[3] = {x2,y2,z2};
      fwrite(pos1, sizeof(double), 3, fileout);
      fwrite(pos2, sizeof(double), 3, fileout);
    }
  fclose(fileout);

  std::cout << "Writing cosmic_masses.bin..." << std::endl;

  fileout = fopen("./OUTPUTS/cosmic_masses.bin", "wb");

  double mass;
  int degree;
  for (i = 0; i < nodelist.size(); i++)
    {
      mass = nodelist[i]->GetM();
      fwrite(&mass, sizeof(double), 1, fileout);
    }
  fclose(fileout);

  std::cout << "Writing cosmic_degree.bin..." << std::endl; 

  fileout = fopen("./OUTPUTS/cosmic_degree.bin", "wb");

  for (i = 0; i < nodelist.size(); i++)
    {
      degree = (nodelist[i]->GetNeighborCount());
      fwrite(&degree, sizeof(int), 1, fileout);
    }
  fclose(fileout);
  std::cout << "Finalized. Program will now terminate." << std::endl;
}
#endif


#ifdef RANDOM_SMALL_WORLD
void globalfns::SW_Finalize(SW_Graph * graph)
{
  unsigned int i = 0;
  int count = graph->GetNodeCount();
  int edgecount;
  //std::ofstream fileout("vertices.bin", std::ios::binary);  
  FILE * fileout = fopen("./OUTPUTS/sw_vertices.bin", "wb");
  std::vector<std::vector<int> > Edges = graph->GetEdges();
  
  std::cout << "Writing sw_vertices.bin..." << std::endl;
  
  fwrite(&count, sizeof(int), 1, fileout);
  edgecount = Edges.size();
  for (i = 0; i < edgecount; i++)
    {
      fwrite(&Edges[i][0], sizeof(int), 1, fileout);
      fwrite(&Edges[i][1], sizeof(int), 1, fileout);
    }  

  std::cout << "Finished. Program will now terminate." << std::endl;
}
#endif //RANDOM_SMALL_WORLD
