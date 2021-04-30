# Bidirectional-AStar

## Problem Inroduction :
A-Star algorithms solve the shortest path problem by iteratively relaxing the next closest node with the smallest estimated distance. Bidirectional A-Star solves the same problem by running the A-Star algorithm both from source and target at the same time till the same node is visited in both forward and backward search. Minimum distance is then the minimum of the estimate till this point. Given a grpah with nodes, edges and coordinates, the algorithm needs to answer queries of minimum distance between sets of source and target.

## Underlying Concept :
A-Star uses admissable heuristics based on certain potential function which is valid for the problem based on how it is posed. The potential function could be as simple as distance between the points on a map. The main thing to be kept in mind while implementing bidirectional version of the A-Star is to assure that the potential function adds same value to the edges in both forward and reversed verion of the graph. This can be done by equating the forward and reverse edge weight function and solving for the acceptable potential in both directions. Once the potential is calculated, the problem can be solved using this estimated distance from target in the forward search and from source in the reverse direction as potential which is somewhat similar to bidirectional dijkstra but with added potential.

## Input Format : 
The first line contains two integers 𝑛 and 𝑚 — the number of nodes and edges in the
network, respectively. The nodes are numbered from 1 to 𝑛. Each of the following 𝑛 lines contains the
coordinates 𝑥 and 𝑦 of the corresponding node. Each of the following 𝑚 lines contains three integers
𝑢, 𝑣 and 𝑙 describing a directed edge (𝑢, 𝑣) of length 𝑙 from the node number 𝑢 to the node number 𝑣.
It is guaranteed that 𝑙 ≥ √︀ (𝑥(𝑢) − 𝑥(𝑣))2 + (𝑦(𝑢) − 𝑦(𝑣))2 where (𝑥(𝑢), 𝑦(𝑢)) are the coordinates of 𝑢
and (𝑥(𝑣), 𝑦(𝑣)) are the coordinates of 𝑣. The next line contains an integer 𝑞 — the number of queries
for computing the distance. Each of the following 𝑞 lines contains two integers 𝑢 and 𝑣 — the numbers
of the two nodes to compute the distance from 𝑢 to 𝑣.

## Constraints : 
1 ≤ 𝑛 ≤ 110 000; 1 ≤ 𝑚 ≤ 250 000; −109 ≤ 𝑥, 𝑦 ≤ 109; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 0 ≤ 𝑙 ≤ 100 000; 1 ≤ 𝑞 ≤ 10 000.

## Output Format :
For each query, output one integer. If there is no path from 𝑢 to 𝑣, output −1. Otherwise,
output the distance from 𝑢 to 𝑣.
