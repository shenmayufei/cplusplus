#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

/***
 * This problem has the same inputs and outputs.  
 * The only difference is that scale of data sets.
 * For this problem, matrix A is of 1 <= n, m <= 100. (col, row)
 * which is much larger (10x) than Problem 2.  
 * I will try Duality method to solve the problem.
 ***/

using namespace std;

typedef vector<vector<double>> matrix;

pair<int, vector<double>> allocate_ads(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  // Write your code here

  return {0, vector<double>(m, 0)};
}

int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = allocate_ads(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
