#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits.h>
#include "MovieNode.hpp"

using namespace std;

class MovieNode;

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
        dist = INT_MAX;
        prev = nullptr;
        done = false;
    }

};

#endif
