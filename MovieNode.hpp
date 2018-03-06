#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class MovieNode {

  public:

    // Fields
    vector<ActorNode*> actors_list;
    string movie_name;

    MovieNode(string * name) {
        movie_name = *name;
        //actors_list.push_back(actor);
    }
}
