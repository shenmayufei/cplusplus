# Problem: Adding Exits to a Maze

## Problem Introduction
Now you decide to make sure that there are no dead zones in a maze, that is, that at least one exit is
reachable from each cell. For this, you find connected components of the corresponding undirected graph
and ensure that each component contains an exit cell.

## Problem Description
**Task.** Given an undirected graph with 𝑛 vertices and 𝑚 edges, compute the number of connected components
in it.
**Input Format.** A graph is given in the standard format.
**Constraints.** 1 ≤ 𝑛 ≤ 103, 0 ≤ 𝑚 ≤ 103.
**Output Format.** Output the number of connected components.