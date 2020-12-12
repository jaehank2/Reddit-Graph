# Sanity check for SSCs output

import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd

myGraph = nx.DiGraph() # create graphviz object
df = pd.read_csv("connected.csv") # load data from csv file
myedges = [] 
for index, row in df.iterrows():
    myedges.append([row['SOURCE_SUBREDDIT'], row['TARGET_SUBREDDIT'], row['LINK_SENTIMENT']*row['count']]) 
myGraph.add_weighted_edges_from(myedges) # load data into graph
res = [len(c) for c in sorted(nx.strongly_connected_components(myGraph), key=len, reverse=True)]
print(res[:20])