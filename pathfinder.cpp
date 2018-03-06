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
#include <limits.h>
# define INF 0x3f3f3f3f

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

        // Initialize the file stream
        ifstream infile(argv[2]);
        bool have_header = false;
        string s;

        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;

            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }

        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }

        string actor1(record[0]);
        string actor2(record[1]);
        bool success;

        if (**(argv[1]) == 'u') {
                success = ag.UnweightedPath(actor1, actor2, argv[3]);

        } else {
                success = ag.WeightedPath(actor1, actor2, argv[3]);

        }

        if (success == false) {
                exit(-1);
        }

        auto it = ag.actors.begin();
        for(; it != ag.actors.end(); ++it ) {
                it->ActorNode.dist = INF;
                it->prev = nullptr;
                it->done = false;
        }


}
