/*
 * ActorGraph.hpp
 * Author: Jennifer Chan
 * Date:   March 5, 2018
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include "ActorNode.hpp"
#include "MovieNode.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <map>
#include <bits/stdc++.h>
#include <limits.h>

// Maybe include some data structures here

using namespace std;

class myComparator {
public:
        int operator()( ActorNode* a, ActorNode* b) {
                return a->dist > b->dist;
        }
};

class ActorGraph {
protected:



public:
    // Maybe add class data structure(s) here
    unordered_map<string, ActorNode> actors;
    unordered_map<string, MovieNode> movies;
    int totalNodes;
    int totalMovies;

    //ActorGraph(const string in_filename, const char * type) ;

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
    //bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    // Function for unweighted graphs
    //bool UnweightedPath(string actor1, string actor2, const string in_filename);

    // Function for weighted graphs
    //bool WeightedPath(string actor1, string actor2, const string in_filename);



	ActorGraph(const char* in_filename, const char * type) {
		bool use_weighted_edges;

		if (*(type) == 'u') {
			use_weighted_edges = false;
		} else {
			use_weighted_edges = true;
		}

		totalNodes = 0;
		totalMovies = 0;

		bool success = loadFromFile(in_filename, use_weighted_edges);
	}

	bool loadFromFile(const char* in_filename, bool use_weighted_edges) {
	    // Initialize the file stream
	    ifstream infile(in_filename);
	    bool have_header = false;

	    // keep reading lines until the end of file is reached
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

		if (record.size() != 3) {
		    // we should have exactly 3 columns
		    continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);

		// Add actor and movies to their respective vectors

		// Check if the actor already exist
		auto it1 = actors.find(actor_name);

		// Check if the movie exists
		auto it2 = movies.find(movie_title + record[2]);

		// If the actor and movie hasn't exist yet, insert into hash map
		if (it1 == actors.end() && it2 == movies.end()) {
			actors.insert({actor_name, ActorNode(&actor_name)});
			movies.insert({movie_title + record[2], MovieNode(&movie_title, movie_year, use_weighted_edges)});
			it1 = actors.find(actor_name);
			it2 = movies.find(movie_title + record[2]);
			totalNodes++;
			totalMovies++;

		// If only the actor hasn't existed yet
		} else if (it1 == actors.end()) {
			actors.insert({actor_name, ActorNode(&actor_name)});
			it1 = actors.find(actor_name);
			totalNodes++;

		// If only the movie hasn't existed yet
		} else if (it2 == movies.end()) {
			movies.insert({movie_title + record[2], MovieNode(&movie_title, movie_year, use_weighted_edges)});
			it2 = movies.find(movie_title + record[2]);
			totalMovies++;

		}

		it1->second.movies_list.push_back(&(it2->second));
		it2->second.actors_list.push_back(&(it1->second));


	    }

	    if (!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	    }
	    infile.close();

	    return true;
	}

	bool UnweightedPath(string actor1, string actor2, ofstream& myfile) {
            cout << "Here" << endl;
	    queue<ActorNode*> toExplore;
	    ActorNode* start;
            string path_obj = "";
	    string & path = path_obj;


	    auto it1 = actors.find(actor1);
	    auto it2 = actors.find(actor2);

	    if (it1 == actors.end()) {
		cout << "Failed to locate node " + actor1 << endl;
		return false;
	    }

	    if (it2 == actors.end()) {
		cout << "Failed to locate node " + actor2 << endl;
		return false;
	    }

	    start = &(it1->second);
	    start->dist = 0;
	    toExplore.push(start);

	    while( !toExplore.empty() ) {
		// Dequeue the front
		ActorNode* next = toExplore.front();
		toExplore.pop();

		// explore all the neighbors starting with each movie
		auto itV = next->movies_list.begin();
		for (; itV != next->movies_list.end(); ++itV) {
			// go to the actors of each movie list
			auto itA = (*itV)->actors_list.begin();
			for (; itA != (*itV)->actors_list.end(); ++itA) {
				ActorNode* neighbor = *itA;
				// once reach actor2, print path
				if (neighbor->actor_name == actor2) {
					//print_to_output(next, myfile);
					print_to_output(next, path);
					path += "[" + (*itV)->movie_name + "#@" + to_string((*itV)->movie_year) + "]";
					path += "-->(" + neighbor->actor_name + ")\n";
					myfile << path;
					return true;
				}
				if (neighbor->dist == INT_MAX) {
					neighbor->dist = next->dist+1;
					neighbor->prev = next;
					//neighbor->prevEdge = make_pair((*itV)->movie_name,(*itV)->movie_year);
					neighbor->prevEdge = (*itV);
					toExplore.push(neighbor);
				}
			}

		}
	    }

	    return false;
	}

	bool WeightedPath(string actor1, string actor2, ofstream& myfile) {
	    priority_queue<ActorNode*, vector<ActorNode*>, myComparator> toExplore;
	    ActorNode* next;
	    ActorNode* start;
	    ActorNode* neighbor;
            string path_obj = "";
	    string & path = path_obj;
	    unordered_map<string,int> visited_movies;

	    auto it1 = actors.find(actor1);
	    auto it2 = actors.find(actor2);

	    if (it1 == actors.end()) {
		cout << "Failed to locate node " + actor1 << endl;
		return false;
	    }

	    if (it2 == actors.end()) {
		cout << "Failed to locate node " + actor2 << endl;
		return false;
	    }

	    start = &(it1->second);
	    start->dist = 0;

	    // vector of distances Initialize to 0
	    toExplore.push(start);

	    while( !toExplore.empty() ) {
		// Dequeue the front
		next = toExplore.top();
		if (next->actor_name == actor2) {
			break;
		}
		int dist = next->dist;
		toExplore.pop();

		// Check if the vertex's min path hasn't been discovered
		if (next->done == false) {
			next->done == true;

			// explore all the neighbors starting with each movie
			auto itV = next->movies_list.begin();
			for (; itV != next->movies_list.end(); ++itV) {
				if (visited_movies.find((*itV)->movie_name) != visited_movies.end()) {
					continue;
				}
				visited_movies.insert({(*itV)->movie_name, 1});	
				int weight = (*itV)->weight;
				// go to the actors of each movie list
				
				auto itA = (*itV)->actors_list.begin();
				for (; itA != (*itV)->actors_list.end(); ++itA) {
					neighbor = (*itA);
					if (neighbor->actor_name == next->actor_name) {
					  continue;
					}

					// find total distance from next to neighbor
					int distance = dist + weight;
					// if a smaller weight path has been found, update
					if (distance < neighbor->dist) {
						neighbor->prev = next;
						neighbor->dist = distance;
						neighbor->prevEdge = (*itV);
						toExplore.push(neighbor);
					}
				}

			}
		}
	    }
	    if (it2->second.dist != INT_MAX) {
		    print_to_output(it2->second.prev, path);
		    path += "[" + it2->second.prevEdge->movie_name + "#@" + to_string(it2->second.prevEdge->movie_year) + "]";
		    path += "-->(" + it2->second.actor_name + ")\n";
		    myfile << path;
		    return true;
	    } else {
		return false;
	    }
	}
	void print_to_output(ActorNode* actor, string & myfile) {

		if (actor->prev == nullptr) {
			myfile += "(" + actor->actor_name + ")--";
		} else {

			print_to_output(actor->prev, myfile);

			myfile += "[" + actor->prevEdge->movie_name + "#@" + to_string(actor->prevEdge->movie_year) + "]-->";
			myfile += "(" + actor->actor_name + ")--";
		}


	}

	int findDegree(ActorNode* actor) {
	  int degree = 0;
	  unordered_map<string, int> co_actors;

	  // Loop through every movie to go to connecting actors to count degree
	  for (int i = 0; i < actor->movies_list.size(); i++) {
	    for (int j = 0; j < actor->movies_list[i]->actors_list.size(); j++) {
	      if (actor->movies_list[i]->actors_list[j] == nullptr) {
	        continue;
	      } else if (actor->movies_list[i]->actors_list[j]->actor_name == actor->actor_name) {
		  continue;
	      } else if (co_actors.find(actor->movies_list[i]->actors_list[j]->actor_name) != co_actors.end()) {
		  continue;
	      }
	      co_actors.insert({actor->movies_list[i]->actors_list[j]->actor_name,1});
              degree++;
	     }
          }

          return degree;
	}

	string graphDecomposition(int k) {
	  ActorNode* node;
          ActorNode* currentNode;
	  int degree;
          string invited = "";
          unordered_map<string,int> nodesDegrees(totalNodes);
          queue<ActorNode*> notInvited;
          unordered_map<string, ActorNode*> invite;

	  // Loop through all the actor nodes and find their degrees
	  auto it = actors.begin();
	  for (; it != actors.end(); ++it) {
	    node = &(it->second);
	    degree = findDegree(node);
            nodesDegrees.insert({node->actor_name, degree});
	    if (degree < k) {
	      notInvited.push(node);
            }
 
	    else {
              invite.insert({node->actor_name, node});
	    }

	  }

	  cout << "Done creating degrees graph" <<endl;

	  // Perform DFS on all the uninvited nodes
	  while (!notInvited.empty()) {
            currentNode = notInvited.front();
            notInvited.pop();

            // Check if the popped queue is still in nodesDegree
            if (nodesDegrees.find(currentNode->actor_name) != nodesDegrees.end()) {
              DFS(currentNode, nodesDegrees, k);
            }

	  }

	  // Double check on all the nodes' degrees that are left in the map
          auto iD = invite.begin();
          for (; iD != invite.end(); ++iD) {
	    degree = findDegree((iD->second));
	    if (degree < k) {
	      iD->second = nullptr;
	    }
          }

          // Loop to append string of invited actors
          auto i = invite.begin();
          for (; i != invite.end(); ++i) {
	    if (i->second == nullptr) {
	      continue;
	    }
            invited += i->first + "\n";
          }

          return invited;

	}

	void DFS(ActorNode* currentNode, unordered_map<string,int> &nodesDegrees, int k) {
          int deg = 0;
	  ActorNode * neighbor;

          // Erase the current from the nodesDegree
          nodesDegrees.erase(currentNode->actor_name);

	  // Iterate through all the neighbors and update nodesDegree
          auto itM = currentNode->movies_list.begin();
          for (; itM != currentNode->movies_list.end(); ++itM) {
            auto itA = (*itM)->actors_list.begin();
            for (; itA != (*itM)->actors_list.end(); ++itA) {
	      if ((*itA) == nullptr) {
	        continue;

              // Delete the current node from actors list
	      } else if ((*itA)->actor_name == currentNode->actor_name) {
                (*itA) = nullptr;

              } else {
                // Decrement the degree of neighbor node and call DFS if it's less than k
                // Then delete actor node pointer from the movie list
                auto it = nodesDegrees.find((*itA)->actor_name);
	        if (it == nodesDegrees.end()) {
		  continue;
		} 
		it->second--;
                if (it->second < k) {
                  neighbor = (*itA);
                  (*itA) = nullptr;
                  DFS(neighbor, nodesDegrees, k);
                }
	      }
            }
          }
	}

};


#endif // ACTORGRAPH_HPP
