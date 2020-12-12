import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd

class GraphVisualization: 
   
    def __init__(self):
        self.G = nx.Graph()        

    def addEdges(self, df):
        myedges = [] 
        for index, row in df.iterrows():
            myedges.append([row['SOURCE_SUBREDDIT'], row['TARGET_SUBREDDIT'], row['LINK_SENTIMENT']*row['count']]) 
        self.G.add_weighted_edges_from(myedges) 
          
    
    def visualize(self):  
        return [len(c) for c in sorted(nx.connected_components(self.G), key=len, reverse=True)]
        # nx.draw_networkx(self.G)
        # print("Done drawing") 
        # plt.show() 
    

    def getLargest(self):
        return max(nx.connected_components(self.G), key=len)

myGraph = GraphVisualization() # create graphviz object
df = pd.read_csv("../data/cleaned.csv") # load data from csv file
myGraph.addEdges(df) # load data into graph

res = myGraph.visualize() # get list of connected components
print("Number of connected subgraphs: " + str(len(res))) 
print("Number of vertices in each subgraph: ") 
print(res)

bigBoi = myGraph.getLargest() # gets all vertices of largets connected graph
print("Number of vertices in largest connected subgraph: " + str(len(bigBoi))) 

toDrop = [] # list to track which rows to delete 
count = 0 # track number of edges retained
for index, row in df.iterrows():
    if row['SOURCE_SUBREDDIT'] in bigBoi and row['TARGET_SUBREDDIT'] in bigBoi: # retains row if both src and des subreddit are in largest connected subgraph
        count += 1 # increments count of retained edges
    else:
        toDrop.append(index) # adds row number to delete from graph if src and des subreddit are not in largest connected component

print("Number of edges in largest connected subgraph: " + str(count))
print("Number of edges dropped from original CSV: " + str(len(toDrop))) 

df2 = df.drop(toDrop) # creates copy of csv data and deletes edges not in largest connected graph


df2.to_csv("../data/connected.csv", index=False) # saves edge data of largest connected subgraph to csv

print("\nSanity check:")
cleaned = GraphVisualization() # create graphviz object
cleaned.addEdges(df2) # load data from csv file
res = cleaned.visualize() # get list of connected components
print("Number of connected subgraphs in largest connected subgraph: " + str(len(res))) 
print("Number of vertices in largest connected subgraph: " + str(res[0])); 

