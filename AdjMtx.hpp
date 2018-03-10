#ifndef ADJMATX
#define ADJMATX

#include <csstdlib>
#include "MatrixMultiply.hpp"
#include "ActorGraph.hpp"
 

using namespace std;

class AdjMtx {

public:

   int sizeMtx;	// size of matrix
   unordered_map<string, int> actorsList;	//unorered map to map actors to index #

  // Constructor
  <vector<vector<int>> AdjMtx(ActorGraph & graph) {
    sizeMtx = graph.actors.size();
    int index = 0;

    // Initialize matrix to all values of 0
    <vector<vector<int>> adjMtx(sizeMtx, vector<int>(sizeMtx, 0));
    auto it = graph.begin();
    for (; it != graph.actors.end(); ++it) {
      actorsList.insert({it->first, index});
      index++;
    }
	
    // Input corresponding values according to relations of the graph
    auto itA = graph.actors.begin();
    for (; itA != graph.actors.end(); ++itA) {
       auto itV = (*itA)->movies_list.begin();
       for (; itV != (*itA)->movies_list.end(); ++itV) {
           auto itM = (*itV)->actors_list //TODO
           vector[actorsList.find(itA->actor_name)][actorsList.find(
       }
    }

    return adjMtx;

  }
/*
  int sizeMtx;
  int ** adjMtx;
  
  //Constructor
  AdjMtx(int size) {
    sizeMtx = size;
    adjMtx = new int* [size];

    for (int i = 0; i < size; i++) {
      adjMtx[i] = new int [size];
   
      for (int j = 0; j < size; j++) {
        adj[i][j] = 0;
      }
    }
	
  }

  
  
  // Destructor
  ~AdjMtx() {
    for (int i = 0; i < sizeMtx; i++) {
      delete[] adjMtx[i];
    }

    delte[] adjMtx;

  }

*/
};

#endif
