/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.hpp"

using namespace std;

int run(int argc, const char ** argv) {
        if (argc < 4) {
                cout << "Incorrect number of arguments." << endl;
                exit(-1);
        }

        // Make the graph with the movie cast list
        ActorGraph ag(argv[0], argv[1]);
        cout << "# nodes: " + ag.totalVertices << endl;
        cout << "# movies: " + ag.totalMovies << endl;
        cout << "# edges:" + ag.totalEdges << endl;



}
