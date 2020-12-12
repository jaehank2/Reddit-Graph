#include "reddit.h"
using namespace std;

/**
 * Constructor
 * @param filename - filepath of dataset
 */
Reddit::Reddit(string filename) : g_() , gT_()// create empty, weighted, and directed graph and its transpose
{
    ifstream f(filename); //input file stream - file pointer
    if(!f.is_open()) 
    {
        cout << filename << " not found!" << endl; // error message
        return;
    }
    string str;
    getline(f, str); //skips first line of csv - coloumn headers

    string src; // temp string to parse source subreddit
    string des; // temp string to parse target subreddit
    string sent; // temp string to parse link sentiment - edge weight
    string count; // temp string to parse #links averaged - edge label


    int num = 0;
    while(1) // loops forever - breaks when end of file is reached
    {
        getline(f, src, ','); // reads till first comma, inserts data in 'src'
        getline(f, des, ','); // reads till second comma, inserts data in 'des' 
        getline(f, sent, ','); // reads till third comma, inserts data in 'sent'
        getline(f, count, '\n'); // reads till end of line, inserts data in 'count'
        if(f.eof()) break; // if end of file is reached - breaks

        if(!g_.vertexExists(src)) g_.insertVertex(src); // if source subreddit doesnt exist, insert to graph
        if(!g_.vertexExists(des)) g_.insertVertex(des); // if target subreddit doesnt exist, insert to graph
        if(!g_.edgeExists(src, des)) // if edge connecting src & des doesnt exist:
        {
            bool attempt = g_.insertEdge(src, des); // insert edge
            int w = stof(sent) * stoi(count); // calculate edge weight
            g_.setEdgeWeight(src, des, w); // set edge weight
            g_.setEdgeLabel(src, des, count); // set edge label
            if(!attempt) cout << "Failed to insert edge connecting '" << src << "' and '" << des << "'" << endl; // error message
        }

        // Same process as above for the graphs transpose:

        if(!gT_.vertexExists(src)) gT_.insertVertex(src); // if source subreddit doesnt exist, insert to graph transpose
        if(!gT_.vertexExists(des)) gT_.insertVertex(des); // if target subreddit doesnt exist, insert to graph transpose
        // order of edge is reversed from (src, des) to (des, src) in order to create transpose
        if(!gT_.edgeExists(des, src)) // if edge connecting des & src doesnt exist:
        {
            bool attempt = gT_.insertEdge(des, src); // insert edge
            int w = stof(sent) * stoi(count); // calculate edge weight
            gT_.setEdgeWeight(des, src, w); // set edge weight
            gT_.setEdgeLabel(des, src, count); // set edge label
            if(!attempt) cout << "Failed to insert transpose edge connecting '" << des << "' and '" << src << "'" << endl; // error message
        }
    }
    f.close(); // close .csv file
}

/**
 * Breadth First Search 
 * @param src - Source vertex
 * @param goal - Target vertex
 * @return BFS path in reverse order
 */
vector<Vertex> Reddit::BFS(Vertex src, Vertex goal)
{
    if(!g_.vertexExists(src)) // Checks if Source subreddit exists
    {
        cout << "Vertex '" << src << "' doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    if(!g_.vertexExists(goal)) // Checks if Goal subreddit exists
    {
        cout << "Vertex '" << goal << "' doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    queue<Vertex> q; //initialize queue to add adjecent vertices
    unordered_map<Vertex, Vertex> prev; // initialize map to track prev vertex
    q.push(src); // add source vertex to queue
    Vertex curr; // initializes current vertex variable

    while(!q.empty()) // loops till all vertices are explored or goal is found
    {
        curr = q.front(); // assigns q front to current vertex
        q.pop(); // removes current vertex from queue
        vector<Vertex> vertex_list = g_.getAdjacent(curr);  // gets a list of adjacent vertices for current vertex
        for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
        {
            if (prev.find(vertex_list[i]) == prev.end()) // checks if this adjecent vertex is unvisted
            {
                prev[vertex_list[i]] = curr; // sets current vertex as previous vertex for this adjecent vertex
                q.push(vertex_list[i]); // adds this adjecent vertex to queue
                if (vertex_list[i] == goal) break; // breaks from for-loop if this adjecent vertex is the goal 
            }
        }
        if (q.back() == goal) break; // breaks from while-loop if the last vertex in the is the goal
    }
    
    vector<Vertex> path; // intializes vector to store output path
    if(q.empty()) return path; // if goal not found returns empty path

    curr = q.back(); // sets current vertex to goal
    path.push_back(curr); // pushes goal in path vector
    while(curr != src) // loops till all the vertices in the path have been pushed
    {
        curr = prev[curr]; // sets current vertex to its previous vertex
        path.push_back(curr); // pushes previous vertex to the path
    }
    return path; // returns reverse path
}


/**
 * Iterative Deepening Search - Calls IDSutil iteratively increasing depth after every iteration 
 * @param src - Source vertex
 * @param goal - Target vertex
 * @return DFS path in reverse
 */
vector<Vertex> Reddit::IDS(string src, string goal, int depth)
{
    if(!g_.vertexExists(src)) // Checks if Source subreddit exists
    {
        cout << "Vertex '" << src << "' doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    if(!g_.vertexExists(goal)) // Checks if Goal subreddit exists
    {
        cout << "Vertex '" << goal << "' doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    vector<Vertex> path; // intializes vector to store output path
    unordered_set<Vertex> visited; // initializes set to track visited vertices
    for (int d = 0; d <= depth; d++) // iteratively increases search depth
    { 
        if(IDSutil(visited, path, src, goal, d)) break; // if goal is found breaks from loop
        path.clear(); // clears path for next IDS
        visited.clear(); // clears visited tracker for next IDS
    }
    return path;
}

/**
 * perform iterative deepening search from a starting node until 
 * goal is found or until the depth goes out of the given bound
 * @param visited - Unoreded set to track visted nodes - passed as reference
 * @param path - Vector of vertices that store the path traversed - passed as reference
 * @param node - Source Vertex
 * @param goal - Target Vertex
 * @param depth - Upper depth limit
 * @return whether target successfully found
 */
bool Reddit::IDSutil(unordered_set<Vertex> & visited, vector<Vertex> & path, Vertex node, Vertex goal, int depth) {  
    if (node == goal){  // if target subreddit found, return true
        path.push_back(goal); // adds goal vertex to path
        return true;
    }
    if (depth <= 0){ //if depth limit reached return false
        return false;
    }
    visited.insert(node); // marks current vertex as visted
    vector<Vertex> vertex_list = g_.getAdjacent(node);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++)
    {
        if(visited.find(vertex_list[i]) == visited.end()) // checks if vertex is unvisted
        {
            if (IDSutil(visited, path, vertex_list[i], goal, depth - 1)) // recursive call to IDSutil with decreased depth
            {
                path.push_back(node); // adds current vertex to path
                return true; // goal found
            }
        }
    }
    visited.erase(node); // marks current vertex as unvisted
    return false; //goal not found
}

/**
 * Kosaraju's Strongly Connected Components
 * @return - Vector of all Strongly Connected Components represented as vectors of vertices
 */
vector<vector<Vertex>> Reddit::SCCs()
{
    vector<vector<Vertex>> res; // Vector to store Strongly Connected Components
    vector<Vertex> vertices = g_.getVertices(); // Gets list of all vertices needed to be explored
    unordered_set<Vertex> visited; // Unordered set to track visited vertices
    vector<Vertex> s; // Stack of vertices to store order of exploration of graph(g_)
    for(size_t i = 0; i < vertices.size(); i++) // iterate over all vertices in graph
    {
        if(visited.find(vertices[i]) == visited.end()) // checks if vertex is unvisted in g_
        {
            SCCUtil(vertices[i], g_, visited, s); // fills stack(s) with vertices reachable via DFS from this vertex
        }
    }

    visited.clear(); // clears unordered set in order to track visited vertices of graph transpose
    
    while(!s.empty()) // loops till SCCs of each vertex have been found 
    {
        Vertex curr = s.back(); // gets top vertex from exploration order stack
        s.pop_back(); // removes top vertex from exploration order stack
        if(visited.find(curr) == visited.end()) // checks if vertex is unvisted in gT_
        {
            vector<Vertex> scc; // Stack of vertices to store SCCs of a given vertex
            SCCUtil(curr, gT_, visited, scc); // fills stack(ssc) with SCCs of this vertex
            res.push_back(scc);
        }
    }
    return res; // returns list of all strongly connected components for this graph
}

/**
 * DFS utility for Kosaraju's strongly connected components
 * @param src - Source vertex
 * @param g - Aliases graph(g_) or graph transpose(gT_)
 * @param visited - Unordered set to keep track of visited nodes
 * @param s - Stack to build order of exploration during non-transpose call and to store SCCs in transpose call
 */
void Reddit::SCCUtil(Vertex src, Graph & g, unordered_set<Vertex> & visited, vector<Vertex> & s)
{
    visited.insert(src); // marks vertex as visted
    vector<Vertex> vertex_list = g.getAdjacent(src);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
    {
        if(visited.find(vertex_list[i]) == visited.end()) // checks if this adjecent vertex is unvisted
        {
            SCCUtil(vertex_list[i], g, visited, s); // calls DFS recursively on adjecent vertex
        }
    }
    s.push_back(src); //add vertex to the stack - see parameters for more detailed explanation of utility
}

/**
 * Tarjans's Strongly Connected Components
 * @return - Vector of all Strongly Connected Components represented as vectors of vertices
 */
vector<vector<Vertex>> Reddit::StronglyCC() {
    vector<Vertex> vertices = g_.getVertices(); // Gets list of all vertices needed to be explored
    vector<vector<Vertex>> result; // 2D vector that stores the strongly connected components
    unordered_map<Vertex, int> dfsnum; // Unordered map that stores the order that node is reached
    unordered_map<Vertex, int> low; // Unordered map that identifies which strongly connected component a node is in
    unordered_set<Vertex> visited; // Unordered set to track vertices currently in the stack
    stack<Vertex> st; // Stack of vertices to store order of exploration of graph(g_)

    for (unsigned i = 0; i < vertices.size(); i++){ // iterates through all unexplored vertices
        if (dfsnum[vertices[i]] == 0){ // checks if vertex has been reached
            StronglyCCUtil(vertices[i], dfsnum, low, st, visited, result); // fills result with strongly connected components given a vertex
        }
    }
    return result; // returns list of all strongly connected components for this graph
} 

/**
 * StronglyCCUtil to find strongly connected components
 * @param curr - Current vertex being observed
 * @param dfsnum - Unordered map that keeps track of which order each node was visited
 * @param low - Unordered map that is used to see which nodes are in the same compnent
 * @param st - Stack that records DFS traversal
 * @param visited - Unordered set that records what nodes are in the stack
 * @param result - 2D vector that stores the strongly connected components
 */
void Reddit::StronglyCCUtil(Vertex curr, unordered_map<Vertex, int> & dfsnum, unordered_map<Vertex, int> & low, stack<Vertex> & st, unordered_set<Vertex> & visited, vector<vector<Vertex>> & result) {
    static int time = 1; // sets a static variable that keeps records the order that nodes are reached
  
    dfsnum[curr] = low[curr] = ++time; // sets dfsnum and low to be time and increments time
    st.push(curr); // pushes vertex to stack
    visited.insert(curr); // Sets that vertex is in the stack
  
    vector<Vertex> adj = g_.getAdjacent(curr); // gets all adjacent vertices
    for (unsigned i = 0 ; i < adj.size() ; i++){ // Iterates through adjacent vertices
        Vertex child = adj[i]; // assignes child to adjacent vertex of the current vertex
  
        if (dfsnum[child] == 0) { // checks if child has been visited
            StronglyCCUtil(child, dfsnum, low, st, visited, result); // DFS iterates through adjacent vertices
            low[curr]  = min(low[curr], low[child]); // On the back track, assigns current low to the minimum of low[curr] and low[child]
        } 
  
        else if (visited.find(child) != visited.end()) // checks if child is added to the stack
            low[curr]  = min(low[curr], dfsnum[child]);  // assigns current low to the minimum of low[curr] and dfsnum[child]
    } 
    Vertex w;
    if (low[curr] == dfsnum[curr]){ // Checks if the order visited equals the lowest value visited
        result.push_back({}); // Adds blank vector to add strongly connected components
        while (st.top() != curr){ // iterates through stack until current node is found
            w = st.top(); // sets w to the top of the stack
            result.back().push_back(w); // pushes top of the stack onto the result vector
            visited.erase(w); // Updates that vertex w is no longer on the stack
            st.pop(); // pops vertex from the stack
        }
        w = st.top(); // sets w to the top of the stack
        result.back().push_back(w); // pushes top of the stack onto the result vector
        visited.erase(w); // Updates that vertex w is no longer on the stack
        st.pop(); // pops vertex from the stack
    } 
} 

/**
 * Full Graph Traversal using DFS
 * @return - Vector of all vertices in graph
 */
vector<Vertex> Reddit::TraversalDFS()
{
    vector<Vertex> explored; // Vector to store all vertices in graph explored through DFS
    unordered_set<Vertex> visited; // Unordered set to track visited vertices
    vector<Vertex> vertices = g_.getVertices(); // Gets vector of all vertices in graph
    for(size_t i = 0; i < vertices.size(); i++) // Iterates over all vertices
    {
        if(visited.find(vertices[i]) == visited.end()) // Checks if vertex is unvisited
        {
            SCCUtil(vertices[i], g_, visited, explored); // If unexplored, DFSs from this vertex and adds all reachable vertices
        }
    }
    return explored; // Returns vector of all vertices in graph explored through DFS
}

/**
 * Path Printing
 * @param vertices - Vector of vertices representing a traversed path
 */
void Reddit::printPath(vector<Vertex> vertices)
{
  if(vertices.empty()) // Checks if input path is empty
  {
    cout << "Empty Path!" << endl; // Prints error message
    return; // Returns
  }

  for(auto it = vertices.rbegin(); it != vertices.rend(); ++it) // Iterates vector in reverse since vertices are added in reverse
  {
    cout << (*it) << " "; // Prints vertex
    if(it + 1 != vertices.rend()) cout << "-> "; // Prints arrow indication path
  }
  cout << endl; // Prints to next line
}

/**
 * Calculates path sentiment
 * @param vertices - Vector of vertices representing a traversed path
 */
float Reddit::getSentiment(vector<Vertex> vertices)
{
  if(vertices.size() < 2) // Checks if input path is long enough
  {
    cout << "Empty Path!" << endl; // Prints error message
    return -1; // Returns -1
  }

  int edges = 0; // Initializes count
  float sentiment = 0; // Initializes sentiment
  
  for(size_t i = 1; i < vertices.size(); i++) // Iterates over vertices starting from second vertex
  {
    float count = stof(g_.getEdgeLabel(vertices[i], vertices[i-1])); // Gets edgelabel - representing number of multiedges added - between current and previous vertex 
    int weight = g_.getEdgeWeight(vertices[i], vertices[i-1]); // Gets edgeweight between current and previous vertex
    sentiment += (weight/count); // Adds average sentiment to sentiment tracker
    edges++; // Increments number of edges explored
  }
  return sentiment/edges; // Returns average sentiment of path 
}

/**
 * Gets Graph
 * @return - Graph object representing the graph of the dataset
 */
const Graph & Reddit::getGraph() const{
    return g_; // Returns graph
}

/**
 * Gets Graph Transpose
 * @return - Graph object representing the graph transpose of the dataset
 */
const Graph & Reddit::getTranspose() const{
    return gT_; // Returns graph transpose
}
