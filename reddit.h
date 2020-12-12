/**
 * @file reddit.cpp
 * CS 225: Data Structures
 */
#pragma once
#include "graph.h"
#include "edge.h"
#include <algorithm>
#include <iostream> 
#include <sstream> 
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using std::unordered_set;
using std::stack;

class Reddit{
    public:
    Reddit(string filename);
    vector<Vertex> BFS(Vertex src, Vertex goal);
    vector<Vertex> IDS(string src, string goal, int depth);
    vector<vector<Vertex>> SCCs();
    vector<vector<Vertex>> StronglyCC();
    vector<Vertex> TraversalDFS();
    void printPath(vector<Vertex> vertices);
    float getSentiment(vector<Vertex> vertices);
    const Graph & getGraph() const;
    const Graph & getTranspose() const;

    private:
    bool IDSutil(unordered_set<Vertex> & visited, vector<Vertex> & path, Vertex node, Vertex goal, int depth);
    void SCCUtil(Vertex src, Graph & g, unordered_set<Vertex> & visited, vector<Vertex> & s);
    void StronglyCCUtil(Vertex u, unordered_map<Vertex, int> & disc, unordered_map<Vertex, int> & low, stack<Vertex> & st, unordered_set<Vertex> & stackMember, vector<vector<Vertex>> & result);
    
    Graph g_;
    Graph gT_;
};   
