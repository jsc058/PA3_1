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
#include <cstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;



// Vector of actors paired with an array of pointers to their movies
//vector<pair<string,ActorNode>> actors;

// Vector of movies
//vector<pair<string,MovieNode>> movies;

ActorGraph::ActorGraph(const string in_filename, const char * type) {
        bool use_weighted_edges;

        if (*(type) == 'u') {
                use_weighted_edges = false;
        } else {
                use_weighted_edges = true;
        }

        bool success = loadFromFile(in_filename.c_str(), use_weighted_edges);
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    // Node to insert into the vectors
    ActorNode * actor;
    MovieNode * movie;

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
        //auto itA = find(actors.begin(), actors.end(), actor_name)

        // Check if the movie exists
        auto it2 = movies.find(movie_title);


        // If the actor and movie hasn't exist yet, insert into hash map
        if (it1 == actors.end() && it2 == movies.end()) {
                actors.insert({actor_name, new ActorNode(&actor_name)});
                movies.insert({movie_title, new MovieNode(*movie_title)});

                totalVertices++;
                totalMovies++;
                totalEdges++;

                //actors.insert({actor_name, vector<string>()});

        // If only the actor hasn't existed yet
        } else if (it1 == actors.end()) {
                actors.insert({actor_name, new ActorNode(&actor_name)});
                totalVertices++;
                totalEdges++;

        // If only the movie hasn't existed yet
        } else if (it2 == movies.end()) {
                movies.insert({movie_title, new MovieNode(&movie_title)});
                totalMovies++;
                totalEdges++;
        }

        it1->second.movies_list.push_back(it2->second);
        it2->second.actors_list.push_back(it1->second);


    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
