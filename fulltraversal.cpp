#include "reddit.h"

int main(int argc, char** argv) 
{
    if(argc != 2) // Ensures corrent number of arguments
    {
        std::cout << "Function requires arguments: [Filepath to data set]" << std::endl; // Prints expected arguments
        return 0; // Returns
    }
    Reddit red(argv[1]); // Creates reddit object using dataset file path
    system("ulimit -s unlimited"); // Set stack size to unlimited
    std::ofstream f; // Creates file object
    int counter = 0; // Internal counter for pretty printing

    vector<Vertex> all = red.TraversalDFS(); // Performs full graph traversal
    std::cout << "Writing full graph traversal to 'traversal.txt'" << std::endl;
    f.open ("traversal.txt"); // Creates text file call traversal.txt to store output
    for(auto v: all) // Iterates over vertices from full graph traversal
    {
        f << v << " "; // Writes vertex to text file
        counter++; // increments counter
        if(counter % 9 == 0) f << "\n"; // ensures only 10 vertices are printed per line
    }

    f.close(); // closes text file
}
