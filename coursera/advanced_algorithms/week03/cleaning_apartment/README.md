# Hamiltonian Path

## My idea: add constraints on edges

1. at most 2 of all edges from vertex u can be selected
2. at least 1 edge from vertex u is selected
3. no cycle is allowed (the task costs too many computing power)

After trying for about one month, I know that this solution doesn't work.

## Idea from hint

One condition variable is defined as: vertex i is at hamiltonian path j, we know `0 <= i, j < numVertices`.

we define all condition as a matrix `vector<vector<bool>> m`, constraints can be described as:

1. for any j, only one of `m[0][j], m[1][j], ..., m[n-1][j]` is true
2. for any i, only one of `m[i][0], m[i][1], ..., m[i][n-1]` is true
3. how edge and m[i][j] are related?