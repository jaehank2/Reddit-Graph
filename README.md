<h1 align="center"> Graph Mining Subreddits </h1>
<h2 align="center"> Yash Gupta | John Kim | Adish Patil | Mike Lee </h2>

## Summary ##
This project uses the [Stanford Reddit Hyperlink Network dataset](http://snap.stanford.edu/data/soc-RedditHyperlinks.html) to provide intresting insights about interactions and conflicts between communities called subreddits on the popular website [Reddit](https://www.reddit.com).

## Data Cleaning ##
The raw data is in a TSV (Tab Seperated Values) format where each line represents a link (see example below). To format this data to our desired format we used python scripts that can be found in the [Python Files](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/tree/master/Python%20Files) folder.

Source Subreddit | Target Subreddit | POST ID | Timestamp           | Sentiment | Post Properties
-----------------|------------------|---------|---------------------|-----------|-----------------
leagueoflegends  | teamredditteams  | 1u4nrps | 2013-12-31 16:39:58 | 1         | 345.0,298.0,... 

For our analysis we decided to to only keep the Source and Target subreddits which would be vertices in our graph and the link sentiment which would represent the edgeweight of the edge connecting these subreddits. To do this we wrote a python script - [cleaner.py](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/Python%20Files/cleaner.py) - which loads the tsv file into a Pandas Dataframe and drops all unwanted information for each link. The raw data also has multiedges - multiple links connecting the same two edges - whose sentiment is added up and the number of multiedges is counted, this cleaned data was then exported to a file called [cleaned.csv](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/data/cleaned.csv) with the following format:

Source Subreddit | Target Subreddit | Sentiment | Count
-----------------|------------------|-----------|-------
leagueoflegends  | teamredditteams  | 1         | 7 

We also wanted to ensure out graph didnt have disconnected vertices. To ensure this we wrote another python script - [cleaner2.py](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/Python%20Files/cleaner2.py) - which loads [cleaned.csv](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/data/cleaned.csv), drops any vertices that arent connected to the larget connected component of the graph using the [NetworkX](https://networkx.org/) library, and saves it to [connected.csv](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/data/connected.csv). This reduces the number of vertices in the dataset from 55,863 to 52,468.

Now our data has no disconnected components, no multiedges and is in the desired format:
Source Subreddit | Target Subreddit | Sentiment | Count
-----------------|------------------|-----------|------- 

### Steps to fomat data: ###
1. Ensure source tsv file "soc-redditHyperlinks-title.tsv" is in the [data](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/tree/master/data) directory.
2. Change to the [Python Files](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/tree/master/Python%20Files) directory using `cd "Python Files"`
3. Ensure all python dependencies are installed using `pip install -r requirements.txt`
4. Run [cleaner.py](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/Python%20Files/cleaner.py) using `python cleaner.py`
5. Run [cleaner2.py](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/Python%20Files/cleaner2.py) using `python cleaner2.py`

## Executables ##
### For users: ###
* BFS
  * Allows users to enter the filepath to dataset, source subreddit, and target subreddit.
  * Prints path from source subreddit to target subreddit and the average sentiment of the path.
  * Compiles [bfsrunner.cpp](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/bfsrunner.cpp) using `make BFS`.
  * Usage - `./BFS [filepath] [source subreddit] [target subreddit]`.
  * Example - `./BFS data/connected.csv 518circlejerk erieco`.
  
* IDS
  * Allows users to enter the filepath to dataset, source subreddit, target subreddit, and maximum search depth.
  * Prints path from source subreddit to target subreddit and the average sentiment of the path.
  * Compiles [idsrunner.cpp](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/idsrunner.cpp) using `make IDS`.
  * Usage - `./IDS [filepath] [source subreddit] [target subreddit] [max depth]`.
  * Example - `./BFS data/connected.csv 518circlejerk erieco 4`.
  
* SCC
  * Allows users to get all strongly connected subreddits using two different algorithms - Kosaraju's and Tarjan's.
  * Writes strongly connected components to kosarajus.txt and tarjanss.txt.
  * Compiles [sccrunner.cpp](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/sccrunner.cpp) using `make SCC`.
  * Usage - `./SCC [filepath]`.
  * Example - `./SCC data/connected.csv`.
  * :warning: ***This executable sets the stack size to unlimited in order to avoid stack overflow with large datasets.*** :warning:
  
* FullTraversal
  * Allows users to traverse over all subreddits in the graph.
  * Writes all visited subreddits to traversal.txt.
  * Compiles [fulltraversal.cpp](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/fulltraversal.cpp) using `make FullTraversal`.
  * Usage - `./FullTraversal [filepath]`.
  * Example - `./FullTraversal data/connected.csv`.
  * :warning: ***This executable sets the stack size to unlimited in order to avoid stack overflow with large datasets.*** :warning:
### For Users/Testers ###
* Test
  * Allows Users/Testers to run our unit tests.
  * 25 test cases with 144 assertions written using 5 [custom testing datasets](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/tree/master/tests) of varying sizes.
  * Compiles [tests.cpp](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/tests/tests.cpp) using `make Test`
  * Usage:
    * Test all - `./Test`
    * Test one function from [constructor, BFS, IDS, Tarjan, Kosaraju, DFSTraversal] - `./Test [function]`
  * Example - `./Test [DFSTraversal]`
* Users
  * Sandbox for Users to write their own function calls for testing.
  * Compiles [datasetTesting.cpp](https://github-dev.cs.illinois.edu/cs225-fa20/yashg3-adish2-jaehank2-dcl3/blob/master/datasetTesting.cpp) using `make TA`.
  * Usage - `./TA`
  * :warning: ***This executable sets the stack size to unlimited in order to avoid stack overflow with large datasets.*** :warning:


**Note:** Unlimited stack size command - `ulimit -s unlimited`
___



