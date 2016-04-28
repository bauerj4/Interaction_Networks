#include "../include/Compile_Time_Options.h"
#include "../include/Proto.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include <cmath>
#include <iostream>

#ifdef COSMIC_WEB
double globalfns::Cosmic_Force(Cosmic_Graph * graph, int NodeID_1, int NodeID_2)
{
  /*
    Returns potential on Node 1 due to Node 2 assuming
    (1) halos are spherical
    (2) halos are non-overlapping
  */

  double x1,x2;
  double y1,y2;
  double z1,z2;
  double r, r2;
  double m1,m2;
  double potential;

#ifdef USE_NFW
  double c1;
  double a1;
  double rho1;
#endif // USE_NFW

  Cosmic_Node * Node1;
  Cosmic_Node * Node2;

  Node1 = graph->GetNode(NodeID_1);
  Node2 = graph->GetNode(NodeID_2);
  
  x1 = Node1->GetX() * HUBBLE; // comoving kpc
  y1 = Node1->GetY() * HUBBLE; // comoving kpc
  z1 = Node1->GetZ() * HUBBLE; // comoving kpc
  m1 = Node1->GetM() * HUBBLE;

  x2 = Node2->GetX() * HUBBLE;
  y2 = Node2->GetY() * HUBBLE;
  z2 = Node2->GetZ() * HUBBLE;
  m2 = Node2->GetM() * HUBBLE;

#ifdef USE_NFW
  c1 = Node1->GetC();
  a1 = Node1->GetA();  
#endif // USE_NFW

  r2 = (x1 - x2) * (x1 - x2);
  r2 += (y1 - y2) * (y1 - y2);
  r2 += (z1 - z2) * (z1 - z2);

  r2 *=  (1./(REDSHIFT + 1.)) * (1./(REDSHIFT + 1.));
  r = sqrt(r2);


  potential = 0.0;

#ifdef USE_KEPLER
  potential = -INTERNAL_G * m2 * m1 / r2;
#endif

#ifdef USE_NFW
  rho1 = m1 * 3. / (4. * M_PI) * (1./340.) * 1./(a1 * a1 * a1);
  m1 = rho1 * 4. * M_PI * (a1 * a1 * a1) *(log((r + a1)/a1) - r/(r + a1));
  potential = -INTERNAL_G * m2 * m1 / r2;
  //std::cout << "M(r), pot = " << m1 << "," << potential << std::endl;
#endif

  return potential;
  
}

#endif // COSMIC_WEB
