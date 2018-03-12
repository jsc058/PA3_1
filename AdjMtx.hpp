#ifndef ADJMATX
#define ADJMATX

#include <cstdlib>
#include "MatrixMultiply.hpp"
#include "ActorGraph.hpp"


using namespace std;

class AdjMtx {

public:

   int sizeMtx;	// size of matrix
   unordered_map<string, int> actorsList;	//unorered map to map actors to index #
   vector<vector<int>> matrix;

  // Constructor
  AdjMtx(ActorGraph & graph) {
    sizeMtx = graph.actors.size();
    int index = 0;
    string * name;


    // Initialize matrix to all values of 0
    vector<vector<int>> matrix(sizeMtx, vector<int>(sizeMtx, 0));
    auto it = graph.actors.begin();
    for (; it != graph.actors.end(); ++it) {
      actorsList.insert({it->first, index});
      index++;
    }

    // Input corresponding values according to relations of the graph
    auto itA = graph.actors.begin();	// Iterator to the ActorGraph actors unordered map
    for (; itA != graph.actors.end(); ++itA) {
       auto itV = (*itA).second.movies_list.begin();	// Iterator through the movies of each actor
       for (; itV != (*itA).second.movies_list.end(); ++itV) {
           auto itM = (*itV)->actors_list.begin();	// Iterator through the actors of the movie
           for (; itM != (*itV)->actors_list.end(); ++itM) {
             matrix[actorsList.at((*itA).second.actor_name)][actorsList.at((*itM)->actor_name)] = 1;
           }
       }
    }

  }

  // Print adjacency matrix
  void print() {
    for (int i = 0; i < sizeMtx; i++) {
      for (int j = 0; j < sizeMtx; j++) {
        cout << matrix[i][j] << " ";
      }
      cout<<endl;
    }
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
