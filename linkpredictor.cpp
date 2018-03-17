#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.hpp"
#include "MatrixMultiply.hpp"
#include <limits.h>

using namespace std;

vector<string> actorsName;
// Function to sort by name if same product value
bool sortbyname(const pair<int,int> &a, const pair<int, int> &b) {
  if (a.second > b.second) {
    return true;
  }

  if (a.second == b.second) {
    return actorsName[a.first] < actorsName[b.first];
  }

  return false;

} 
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
	int sizeMtx = graph.actors.size();	// Total number of actors
	int index = 0;	// Index for the actors in the matrix
	unordered_map<string, int> actorsList;
	vector<vector<int>> matrix(sizeMtx, vector<int>(sizeMtx,0));
	auto it = graph.actors.begin();
        for (; it != graph.actors.end(); ++it) {
	  actorsName.push_back(it->first);
	  actorsList.insert({it->first, index});
	  index++;
	}
	// Input corresponding values according to relations of the graph
	auto itA = graph.actors.begin();	// Iterator to the ActorGraph actors unordered map
	for (; itA != graph.actors.end(); ++itA) {
	  auto itV = (*itA).second.movies_list.begin();	// Iterator through the actor's movies
	  for (; itV != (*itA).second.movies_list.end(); ++itV) {
	    auto itM = (*itV)->actors_list.begin();	// Iterator through the actors of the movie
     	    for (; itM != (*itV)->actors_list.end(); ++itM) {
	      if ((*itM)->actor_name == (*itA).second.actor_name) {
                continue;
              }
	      matrix[actorsList.at((*itA).second.actor_name)][actorsList.at((*itM)->actor_name)] = 1;
	    }
	  }
	}
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

	vector <string> record;
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
		//vector <string> record;

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

	}

	// Make matrix of actors from file
	vector<vector<int>> actorMtx;
	for (int idx = 0; idx < record.size(); idx++) {
	  auto it1 = actorsList.find(record[idx]);
	  if (it1 == actorsList.end()) {
	    cout << "Actor not found" << endl;
	    continue;
          }
          actorMtx.push_back(matrix[it1->second]);
	}

	// Perform matrix operations
	vector<vector<pair<int,int>>> prodMtx;
	MatrixOperations<int> mtx(actorMtx, matrix);
	prodMtx = mtx.matrixMultiply();

	// Sort each row of the matrix and write the top 4 interactions 
	for (int idx2 = 0; idx2 < record.size(); idx2++) {
          sort (prodMtx[idx2].begin(), prodMtx[idx2].end(), sortbyname);
	  vector<string> interactions;	
	  vector<string> collaborators;	
          for (int j2 = 0; j2 < sizeMtx; j2++) {
	    if (actorsName[prodMtx[idx2][j2].first] == record[idx2]) {
	      continue;
            }
	    if (actorMtx[idx2][prodMtx[idx2][j2].first] == 0 && collaborators.size() < 4) {
              collaborators.push_back(actorsName[prodMtx[idx2][j2].first] + "\t");
            } else if (actorMtx[idx2][prodMtx[idx2][j2].first] == 1 & interactions.size() < 4) {
               interactions.push_back(actorsName[prodMtx[idx2][j2].first] + "\t");
	    } else if (collaborators.size() == 4 && interactions.size() == 4) {
		break;
	    }
          }
  	  while (collaborators.size() < 4 ) {
 	    collaborators.push_back("NULL\t");
	  }
  	  while (interactions.size() < 4) {
 	    interactions.push_back("NULL\t");
	  }
	  myfile1 << interactions[0]+ interactions[1]+ interactions[2]+ interactions[3] + "\n";
	  myfile2 << collaborators[0]+ collaborators[1]+ collaborators[2]+ collaborators[3] + "\n";
	  cout << "Computing predictions for " + record[idx2] << endl;
        }

	myfile1.close();
	myfile2.close();

	return 0;

};
