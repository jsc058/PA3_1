#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include "MovieNode.hpp"

using namespace std;

class ActorNode {

  public:

    // Fields
    vector<MovieNode *> movies_list;
    string actor_name;

    ActorNode(string * name) {
        actor_name = *name;
        //movies_list.push_back(movie);
    }

};

#endif
