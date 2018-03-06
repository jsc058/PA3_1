#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include "ActorNode.hpp"

using namespace std;

class MovieNode {

  public:

    // Fields
    vector<ActorNode *> actors_list;
    string movie_name;
    int movie_year;
    int weight;

    MovieNode(string * name, int year, bool use_weighted_edges) {
        movie_name = *name;
        movie_year = year;

        if (use_weighted_edges == true) {
                weight = 1 + (2018-year);
        }

    }

};

#endif
