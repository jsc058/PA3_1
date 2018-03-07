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

//#include "ActorGraph.cpp"
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
#include <bits/stdc++.h>
# define INF 0x3f3f3f3f

// Maybe include some data structures here

using namespace std;

class myComparator {
public:
        int operator()(const pair<int,ActorNode*> &a,
                      const pair<int,ActorNode*> &b) {
                return a.first < b.first;
        }
};

class ActorGraph {
protected:



public:
    // Maybe add class data structure(s) here
    unordered_map<string, ActorNode> actors;
    unordered_map<string, MovieNode> movies;
    int totalVertices;
    int totalEdges;
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



	ActorGraph(const string in_filename, const char * type) {
		bool use_weighted_edges;

		if (*(type) == 'u') {
			use_weighted_edges = false;
		} else {
			use_weighted_edges = true;
		}

		bool success = loadFromFile(in_filename.c_str(), use_weighted_edges);
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
		auto it2 = movies.find(movie_title);

		// If the actor and movie hasn't exist yet, insert into hash map
		if (it1 == actors.end() && it2 == movies.end()) {
			actors.insert({actor_name, ActorNode(&actor_name)});
			movies.insert({movie_title, MovieNode(&movie_title, movie_year, use_weighted_edges)});

			totalVertices++;
			totalMovies++;
			totalEdges++;

		// If only the actor hasn't existed yet
		} else if (it1 == actors.end()) {
			actors.insert({actor_name, ActorNode(&actor_name)});
			totalVertices++;
			totalEdges++;

		// If only the movie hasn't existed yet
		} else if (it2 == movies.end()) {
			movies.insert({movie_title, MovieNode(&movie_title, movie_year, use_weighted_edges)});
			totalMovies++;
			totalEdges++;
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

	bool UnweightedPath(string actor1, string actor2, const string in_filename) {

	    queue<ActorNode*> toExplore;
	    ActorNode* start;
            string * path;


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
					ofstream myfile(in_filename);
					if (myfile.is_open()) {
						print_to_output(neighbor, path);
			    			myfile << *path;
						myfile << "-->(" + neighbor->actor_name + ").\n";
					} else {
						cout << "Unable to open file" << endl;
						return false;
					}
				}
				if (neighbor->prev == nullptr) {
					neighbor->dist = next->dist+1;
					neighbor->prev = next;
					neighbor->prevEdge = make_pair((*itV)->movie_name,(*itV)->movie_year);
					toExplore.push(neighbor);
				}
			}

		}
	    }

	    return false;
	}

	bool WeightedPath(string actor1, string actor2, const string in_filename) {

	    priority_queue<pair<int,ActorNode*>, vector<pair<int,ActorNode*>>, myComparator> toExplore;
	    ActorNode* start;
	    string * path;

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
	    //start->dist = 0;
	    // vector of distances Initialize to 0
	    toExplore.push(make_pair(0,start));

	    while( !toExplore.empty() ) {
		// Dequeue the front
		pair<int,ActorNode*> next = toExplore.top();

		toExplore.pop();

		// Check if the vertex's min path hasn't been discovered
		if (next.second->done == false) {
			next.second->done == true;

			// explore all the neighbors starting with each movie
			auto itV = next.second->movies_list.begin();
			for (; itV != next.second->movies_list.end(); ++itV) {
				// go to the actors of each movie list
				auto itA = (*itV)->actors_list.begin();
				for (; itA != (*itV)->actors_list.end(); ++itA) {
					ActorNode* neighbor = *itA;

					// find total distance from next to neighbor
					int distance = next.second->dist + (*itV)->weight;

					// if a smaller weight path has been found, update
					if (distance < neighbor->dist) {
						neighbor->prev = next.second;
						neighbor->dist = distance;
						toExplore.push(make_pair(distance,neighbor));
					}
				}

			}
		}
	    }

	    if (it2->second.dist != INF) {
		    ofstream myfile(in_filename);
		    if (myfile.is_open()) {
			    print_to_output(&it2->second, path);
			    myfile << *path;
			    myfile << "-->(" + it2->second.actor_name + ").\n";
		    } else {
			    cout << "Unable to open file" << endl;
			    return false;
		    }

	    } else {
		return false;
	    }
	}

	void print_to_output(ActorNode* actor, string* path) {
		ActorNode * prev = actor->prev;

		if (prev == nullptr) {
			//myfile << "(" + actor->actor_name + ")";
			path->append("(" + actor->actor_name + ")"); 
		}

		print_to_output(prev, path);

		//myfile << "--[" + actor->prevEdge.first + "#@" + to_string(actor->prevEdge.second) + "]";
		path->append("--[" + actor->prevEdge.first + "#@" + to_string(actor->prevEdge.second) + "]");


	}
};


#endif // ACTORGRAPH_HPP
