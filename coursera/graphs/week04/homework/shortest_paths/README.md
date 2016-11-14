# 4 Advanced Problem: Exchanging Money Optimally

## Problem Introduction
Now, you would like to compute an optimal way of exchanging the given currency ci
into all other currencies.
For this, you find shortest paths from the vertex ci to all the other vertices.

## Problem Description
**Task.** Given an directed graph with possibly negative edge weights and with n vertices and m edges as well
as its vertex s, compute the length of shortest paths from s to all other vertices of the graph.
**Input Format.** A graph is given in the standard format.
**Constraints.** 1 ≤ n ≤ 10^3, 0 ≤ m ≤ 10^4, 1 ≤ s ≤ n, edge weights are integers of absolute value at most 10^9.
**Output Format.** For all vertices i from 1 to n output the following on a separate line:
1. “*”, if there is no path from s to u;
2. “-”, if there is a path from s to u, but there is no shortest path from s to u (that is, the distance from s to u is −∞);
3. the length of a shortest path otherwise.