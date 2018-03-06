#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <limits.h>
#include "MovieNode.hpp"
# define INF 0x3f3f3f3f

using namespace std;
//numeric_limits<double>::infinity()
class ActorNode {

  public:

    // Fields
    vector<MovieNode *> movies_list;
    string actor_name;
    int dist;
    ActorNode* prev;
    pair<string, int> prevEdge;
    bool done;

    ActorNode(string * name) {
        actor_name = *name;
        dist = INF;
        prev = nullptr;
        done = false;
    }

};

#endif
