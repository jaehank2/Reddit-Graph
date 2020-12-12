import pandas as pd

df = pd.read_csv("../data/soc-redditHyperlinks-title.tsv", sep='\t') # reads .tsv file into pandas dataframe
df.drop(["POST_ID", "TIMESTAMP", "PROPERTIES"], axis=1, inplace = True) # removes POST_ID, TIMESTAMP, and PROPERTIES colums
grouped = df.groupby(["SOURCE_SUBREDDIT", "TARGET_SUBREDDIT"]) # index data using source and target subreddit - allows to average multiedge weights
summed = grouped.mean() # averages multiedge weights
summed['count'] = grouped.count() # counts multiedges
final = summed.reset_index() # flattens multi-index to create [source, target, avg_sentiment, #multiedges] format 
final.to_csv('../data/cleaned.csv', index=False) # saves cleaned dataframe to .csv file
