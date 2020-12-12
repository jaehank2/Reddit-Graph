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
    int counter; // Internal counter for pretty printing

    vector<vector<Vertex>> kosaraju = red.SCCs(); // Stores kosarajus SCCs
    std::cout << "Writing SCCs found using Kosaraju's algorithm to 'kosarajus.txt'" << std::endl;
    f.open ("kosarajus.txt"); // Creates text file call kosarajus.txt to store output
    for(auto & vec : kosaraju) // Iterates over each SCC
    {
        counter = 0; // Sets counter to 0
        for(auto scc: vec) // Iterates over vertices in this SCC
        {
            f << scc << " "; // Writes vertex to text file
            counter++; // increments counter
            if(counter % 9 == 0) f << "\n"; // ensures only 10 vertices are printed per line
        }
        f << "\n***\n"; // Aesthetic purposes
    }
    f.close(); // closes text file

    vector<vector<Vertex>> tarjans = red.StronglyCC(); // Stores tarjans SCCs
    std::cout << "Writing SCCs found using Tarjan's algorithm to 'tarjans.txt'" << std::endl;
    f.open ("tarjans.txt"); // Creates text file call tarjans.txt to store output
    for(auto & vec : tarjans) // Iterates over each SCC
    {
        counter = 0; // Sets counter to 0
        for(auto scc: vec) // Iterates over vertices in this SCC
        {
            f << scc << " "; // Writes vertex to text file
            counter++; // increments counter
            if(counter % 9 == 0) f << "\n"; // ensures only 10 vertices are printed per line
        }
        f << "\n***\n"; // Aesthetic purposes
    }
    f.close(); // closes text file
}
