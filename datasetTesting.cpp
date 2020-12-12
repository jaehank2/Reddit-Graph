#include "reddit.h"


void sccSpeed(Reddit & r); // declares SCC racer
void sccSpeed(Reddit & r)
{
  auto t1 = std::chrono::high_resolution_clock::now(); // Tracks starting time
  r.SCCs(); // Calls kosaraju's SCC
  auto t2 = std::chrono::high_resolution_clock::now(); // Tracks Kosaraju time
  r.StronglyCC(); // Calls tarjan's SCC
  auto t3 = std::chrono::high_resolution_clock::now(); // Tracks end time

  auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count(); // Calculates Kosaraju time
  auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>( t3 - t2 ).count(); // Calculates Tarjan time

  std::cout << "Kosaraju's Algo: " << duration1 << std::endl; // Prints time take for Kosaraju in milliseconds
  std::cout << "Tarjan's Algo: " << duration2 << std::endl; // Prints time take for Tarjan in milliseconds
}

int main() 
{
  std::cout << "This is a testing file to test custom function calls. We hope you enjoy our project!" << std::endl;
  Reddit red("data/connected.csv"); // Creates reddit object
  // WARNING: Due to our large dataset, Both SCC implementations will run into Stack Overflow
  // Set stack size to unlimited using "ulimit -s unlimited" before calling DFSTraversal(), SCCs(), or StronglyCC()
  system("ulimit -s unlimited"); // Set stack size to unlimited
  vector<vector<Vertex>> kosaraju = red.SCCs(); // Kosarajus Strongly Connected Componets Implementation
  vector<vector<Vertex>> tarjan = red.StronglyCC(); // Kosarajus Strongly Connected Componets Implementation
  vector<Vertex> fulltraversal = red.TraversalDFS(); // Full graph DFS Traversal
  vector<Vertex> bfspath = red.BFS("rarepuppers", "erieco"); // Get BFS path
  vector<Vertex> idspath = red.IDS("rarepuppers", "erieco", 4); // Get IDS path
  red.printPath(bfspath); // Print BFS path
  red.printPath(idspath); // Print IDS path
  std::cout << "Path sentiment (BFS): " << red.getSentiment(bfspath) << std::endl; // Print BFS path sentiment
  std::cout << "Path sentiment (IDS): " << red.getSentiment(idspath) << std::endl; // Print IDS path sentiment
  return 0;
}

// Some cool observations: 

// *****************************Search Time & Memory Test*******************************
// Tests for search between "rarepuppers" and "erieco"
// Baseline: total heap usage: 685,787 allocs, 685,787 frees, 77,193,512 bytes allocated
// BFS: total heap usage: 707,555 allocs, 707,555 frees, 83,385,040 bytes allocated 
// IDS: total heap usage: 703,676 allocs, 703,676 frees, 91,823,200 bytes allocated
// Average time for BFS:  51.418 ms
// Average time for IDS: 118.075 ms
// Memeory Allocated BFS:  6.191528 MB 
// Memeory Allocated IDS: 14.629688 MB

// *****************************Search Time & Memory Test*******************************
// Tests between Kosaraju vs Tarjan
// Baseline: total heap usage: 685,787 allocs, 685,787 frees, 77,193,512 bytes allocated
// Kosaraju: total heap usage: 1,331,200 allocs, 1,331,200 frees, 160,113,164 bytes allocated
// Tarjan: total heap usage: 971,122 allocs, 971,122 frees, 110,370,172 bytes allocated
// Memeory Allocated Kosaraju: 82.919552 MB 
// Memeory Allocated Tarjan: 33.176560 MB

// *****************************Search Time & Memory Test*******************************
// Tests between Kosaraju vs Tarjan
// Baseline: total heap usage: 685,787 allocs, 685,787 frees, 77,193,512 bytes allocated
// Kosaraju: total heap usage: 1,018,752 allocs, 1,018,752 frees, 124,308,792 bytes allocated
// Tarjan: total heap usage: 971,122 allocs, 971,122 frees, 110,370,172 bytes allocated
// Memeory Allocated Kosaraju: 47.115280 MB 
// Memeory Allocated Tarjan: 33.176560 MB


// Time comparison for reversing traversal path vs not reversing traversal path:

// Reversing before returning:
// Average time for BFS:  51.418 ms
// Average time for IDS: 118.075 ms

// Not reversing before returning:
// Average time for BFS: 51.378 ms
// Average time for IDS: 99.102 ms

//Constructor: 18
//Kosaraju's Algo: 508
//Tarjan's Algo: 696
//DFS runtime: 248

// Updated:
// Constructor: 16
// Kosaraju's Algo: 547
// Tarjan's Algo: 645
// DFS runtime: 261