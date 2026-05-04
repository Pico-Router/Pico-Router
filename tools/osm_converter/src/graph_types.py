import cppyy

cppyy.include("include/pathfind/graph.h")

from cppyy.gbl import pathfind

Edge = pathfind.Edge
Node = pathfind.Node
Graph = pathfind.Graph
