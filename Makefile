# Executable names:
EXE = TA 
TEST = Test

# Add all object files needed for compiling:
EXE_OBJ = datasetTesting.o
BFS_OBJS = bfsrunner.o reddit.o graph.o
IDS_OBJS = idsrunner.o reddit.o graph.o
SCC_OBJS = sccrunner.o reddit.o graph.o
DFS_OBJS = fulltraversal.o reddit.o graph.o
OBJS = graph.o datasetTesting.o reddit.o


# Use the cs225 makefile template:
include cs225/make/cs225.mk
