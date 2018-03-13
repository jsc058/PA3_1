#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.hpp"
#include <limits.h>

using namespace std;

int main(int argc, const char ** argv) {
	if (argc < 4) {
                cout << "Incorrect number of arguments." << endl;
                exit(-1);
        }

	// Make the graph with the movie cast list
	const char * type = "u";
        ActorGraph ag(argv[1], type);
        ActorGraph & graph = ag;
	cout << "Done creating graph\n" << endl;

	// Call graph decomposition to come up with the invite list
	string invited = ag.graphDecomposition(argv[2]);

	// Output file
        ofstream myfile1(argv[3]);
	ofstream & myfile_ref1 = myfile1;
	if (myfile1.is_open()) {
		myfile_ref1 << "Actor\n";
	}

        myfile_ref1 << invited;

	// Tester for functions; Delete later
	/*
	int degree = 0;
	auto it = ag.actors.begin();
	for (; it != ag.actors.end(); ++it) {
	  ActorNode* node = &(it->second);
	  degree = ag.findDegree(node);
	  cout << node->actor_name + " " + to_string(degree) << endl;
	}
	*/

	myfile1.close();

	return 0;

};
