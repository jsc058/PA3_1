/*
 * ActorGraph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"

// Maybe include some data structures here

using namespace std;

class ActorGraph {
protected:



public:
    // Maybe add class data structure(s) here
    unordered_map<string, vector<MovieNode*>> actors;
    unordered_map<string, vector<ActorNode*>> movies;
    int totalVertices;
    int totalEdges;
    int totalMovies;

    ActorGraph(const string in_filename, const char * type) ;

    // Maybe add some more methods here

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2018 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    pair<int, int> loadFromFile(const char* in_filename, bool use_weighted_edges);

};


#endif // ACTORGRAPH_HPP
