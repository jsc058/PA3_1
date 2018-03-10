#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.hpp"
#include "AdjMtx.hpp"
#include <limits.h>

using namespace std;

int main(int argc, const char ** argv) {

	if (argc < 5) {
                cout << "Incorrect number of arguments." << endl;
                exit(-1);
        }

	// Make the graph with the movie cast list
	const char * type = "u";
        ActorGraph ag(argv[1], type);
        ActorGraph & graph = ag;
	cout << "Done creating graph\n" << endl;

	// Make an adjacency matrix from the graph
	AdjMtx adjMtx(graph);
        adjMtx.print();
	cout << "Done creating mtx\n" << endl;

	// Initialize the file stream
        ifstream infile(argv[2]);
        bool have_header = false;

	// Existing interaction file
        ofstream myfile1(argv[3]);
	ofstream & myfile_ref1 = myfile1;
	if (myfile1.is_open()) {
		myfile_ref1 << "Actor1,Actor2,Actor3,Actor4\n";
	}

	// Links which don't currently exist
        ofstream myfile2(argv[4]);
	ofstream & myfile_ref2 = myfile2;
	if (myfile2.is_open()) {
		myfile_ref2 << "Actor1,Actor2,Actor3,Actor4\n";
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

		    // get the next string  and put it in 'next'
		    if (!getline( ss, next)) break;

		    record.push_back( next );
		}

		if (record.size() != 1) {
		    // we should have exactly 1 column
		    continue;
		}

		string actors(record[0]);

	}


	myfile1.close();
	myfile2.close();

	return 0;

};
