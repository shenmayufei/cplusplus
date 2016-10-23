# Problem Introduction

The police department of a city has made all streets one-way. Eou would like
to check whether it is still possible to drive legally from any intersection to
any other intersection. For this, you construct a directed graph: vertices are
intersections, there is an edge (u; v) whenever there is a (one-way) street from
u to v in the city. Then, it suces to check whether all the vertices in the
graph lie in the same strongly connected component.

# Problem Description
**Task.** Compute the number of strongly connected components of a given directed graph with n vertices and m edges.
**Input Format.** A graph is given in the standard format.
**Constraints.** 1 <= n <= 10^4, 0 <= m <= 10^4.
**Output Format.** Output the number of strongly connected components.