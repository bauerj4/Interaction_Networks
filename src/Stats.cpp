#include "../include/Proto.h"
#include <random>
#include <vector>
#include <cmath>


#ifdef RANDOM_SMALL_WORLD
std::vector<int> globalfns::SerialUnifPair(int a, int b)
{
  int v1 = -1;
  int v2 = -1;
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(a,b);
  std::vector<int> vertex_pair;


  while (v1 == v2 || fabs(v1 - v2) <= Z_SHORT_EDGES/2)
    {
      v1 = rand() % (b-a) + a;//distribution(generator);
      v2 = rand() % (b-a) + a;//distribution(generator);
    }

  vertex_pair.push_back(v1);
  vertex_pair.push_back(v2);

  return vertex_pair;
}
#endif
