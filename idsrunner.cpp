#include "reddit.h"
#include <vector>
#include <string>

int main(int argc, char** argv) 
{
    if(argc != 5) // Ensures correct number of arguments
    {
        std::cout << "Function requires arguments: [Filepath to data set] [Source Subreddit] [Target Subreddit] [Search Depth]" << std::endl; // Prints expected arguments
        return 0; // Returns
    }
    Reddit red(argv[1]); // Creates reddit object using dataset file path
    vector<Vertex> path1 = red.IDS(argv[2], argv[3], atoi(argv[4])); //IDSs from source subreddit to target subreddit until target is found or maximum depth is reached
    std::cout << "IDS path: "; 
    red.printPath(path1); // Prints path
    std::cout << "Path sentiment: " << red.getSentiment(path1) << std::endl; // Prints path sentiment
}
