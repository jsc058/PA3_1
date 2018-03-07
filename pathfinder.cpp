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

using namespace std;



int main(int argc, const char ** argv) {
        if (argc < 5) {
                cout << "Incorrect number of arguments." << endl;
                exit(-1);
        }

        // Make the graph with the movie cast list
        ActorGraph ag(argv[1], argv[2]);
	cout << ag.totalNodes << endl;
	cout << ag.totalMovies << endl;

        // Initialize the file stream
        ifstream infile(argv[3]);
        bool have_header = false;
        ofstream myfile(argv[4]);
	ofstream & myfile_ref = myfile;
	if (myfile.is_open()) {
		myfile_ref << "(actor)--[movie#@year]-->(actor)--...\n";
	}
	while (infile) {
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

		if (strcmp(argv[2],"u") == 0) {
			success = ag.UnweightedPath(actor1, actor2, myfile_ref);

		} else {
			success = ag.WeightedPath(actor1, actor2, myfile_ref);
			cout << actor1 + actor2 << endl;

		}

		auto it = ag.actors.begin();
		for(; it != ag.actors.end(); ++it ) {
			it->second.dist = INT_MAX;
			it->second.prev = nullptr;
			it->second.done = false;
		}
	}
	

	myfile.close(); 
	return 0;
		


};
