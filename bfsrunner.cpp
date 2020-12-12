#include "reddit.h"

int main(int argc, char** argv) 
{
    if(argc != 4) // Ensures correct number of arguments
    {
        std::cout << "Function requires arguments: [Filepath to data set] [Source Subreddit] [Target Subreddit]" << std::endl; // Prints expected arguments 
        return 0; // Returns
    }
    Reddit red(argv[1]); // Creates reddit object using dataset file path
    vector<Vertex> path1 = red.BFS(argv[2], argv[3]); //BFSs from source subreddit to target subreddit
    std::cout << "BFS path: ";
    red.printPath(path1); // Prints path
    std::cout << "Path sentiment: " << red.getSentiment(path1) << std::endl; // Prints path sentiment
}
