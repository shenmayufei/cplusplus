#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

typedef vector<vector<double>> matrix;


/********************************************* 
 * Solve the equation
 * start
 *********************************************/

typedef vector<double> Column;
typedef vector<double> Row;
typedef vector<Row> Matrix;

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

// SelectPivotElement selects the first free element
// the pivot value could be zero (which must be the first position)
// or non-zero value
// actually, column is still the row number (whose value is often not zero)
// the most ideal condition is row==column (whose value is not zero, probably one)
Position SelectPivotElement(
  const Matrix &a, 
  vector <bool> &used_rows, 
  vector <bool> &used_columns) {
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row])
        ++pivot_element.row;
    while (used_columns[pivot_element.column])
        ++pivot_element.column;

    size_t m = used_rows.size();
    size_t n = used_columns.size();
    if (pivot_element.row == m || pivot_element.column == n)
        return pivot_element;  // invalid position

    size_t i = pivot_element.column;
    while(i < n){
        if (a[pivot_element.row][i] != 0) {
            pivot_element.column = i;
            return pivot_element;
        }
        i++;
    }
    return pivot_element;
}

// After swapping, row==column
// the first free element could probably NOT zero, but also possibly is zero
void SwapLines(Matrix &a, Column &b, vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    if (a[pivot_element.row][pivot_element.column] == 0) return;
    size_t n = b.size();

    // set this row pivot value as ONE
    double baseVal = a[pivot_element.row][pivot_element.column];
    for(size_t j = pivot_element.column; j< n; j++) a[pivot_element.row][j] /= baseVal;
    b[pivot_element.row] /= baseVal;

    // update other rows
    for(size_t i = 0; i < n; i++){
        if (i==pivot_element.row) continue;
        if (a[i][pivot_element.column]==0) continue;
        double multBy = a[i][pivot_element.column];
        for(size_t j = pivot_element.column; j < n; j++)
            a[i][j] -= multBy * a[pivot_element.row][j];
        b[i] -= multBy * b[pivot_element.row];
    }
}

void MarkPivotElementUsed(const Position &pivot_element, vector <bool> &used_rows, vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Matrix& a, Column b) {
    int size = a.size();

    vector <bool> used_columns(size, false);
    vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
        // std::cout << "row:" << pivot_element.row << ", column:" << pivot_element.column 
        // << ", value:" << a[pivot_element.row][pivot_element.column] << ", b:" << b[pivot_element.row] <<  std::endl;
        // std::cout << a[1][0] << ", " << a[1][1] << "=>" << b[1] << std::endl;
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        // std::cout << "after process, row:" << pivot_element.row << ", column:" << pivot_element.column 
        // << ", value:" << a[pivot_element.row][pivot_element.column] << ", b:" << b[pivot_element.row]<<  std::endl;
        // std::cout << a[1][0] << ", " << a[1][1] << "=>" << b[1] << std::endl;

        // std::cout << std::endl;
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }

    return b;
}


/********************************************* 
 * Solve the equation
 * end
 *********************************************/

matrix transpose(int n, int m, const matrix& mx) {
  matrix newM(m, vector<double>(m, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      newM[m][n] = mx[n][m];
    }
  }
  return mx;
}

pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  // solve the dual equation
  matrix dualA = transpose(n, m, A);
  vector<double> y = SolveEquation(dualA, c);
  // check the result
  for(int i = 0; i < m; i++) {
    for(int j = i; j< n; j++) {
      if(dualA[i][j]==0) {
        if (y[i]==0) return {1, vector<double>(m,0)};
        else return {-1, vector<double>(m,0)};
      }
    }
  }
  if (m<n) return {1, vector<double>(m,0)};
  else return {0, y};
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

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

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
