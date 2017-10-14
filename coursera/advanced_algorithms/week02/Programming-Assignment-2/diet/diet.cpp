#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const int PRECISION = 20;

typedef vector<vector<double>> matrix;

/****
 * the problem cannot be solved by duality (complementary slackness) after many tries,
 * so I choose to solve it via moving between vertices of a polytope, 
 * namely simplex
 */


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
  std::vector <bool> &used_rows, 
  std::vector <bool> &used_columns) {
    size_t n = used_rows.size();
    size_t m = used_columns.size();

    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row] && pivot_element.row < n)
        ++pivot_element.row;
    while (used_columns[pivot_element.column] && pivot_element.column < m)
        ++pivot_element.column;


    if (pivot_element.row == n || pivot_element.column == m)
        return pivot_element;  // invalid position

    for(size_t i = pivot_element.column; i < n; i++){
        if (a[i][pivot_element.column] != 0) {
            pivot_element.row = i;
            return pivot_element;
        }
    }
    return pivot_element;
}

// After swapping, row==column
// the first free element could probably NOT zero, but also possibly is zero
void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    if (a[pivot_element.row][pivot_element.column] == 0) return;
    size_t n = a.size();
    size_t m = a[0].size();

    // set this row pivot value as ONE
    double baseVal = a[pivot_element.row][pivot_element.column];
    for(size_t j = pivot_element.column; j< m; j++) a[pivot_element.row][j] /= baseVal;
    b[pivot_element.row] /= baseVal;

    // update other rows
    for(size_t i = 0; i < n; i++){
        if (i==pivot_element.row) continue;
        if (a[i][pivot_element.column]==0) continue;
        double multBy = a[i][pivot_element.column];
        for(size_t j = pivot_element.column; j < m; j++)
            a[i][j] -= multBy * a[pivot_element.row][j];
        b[i] -= multBy * b[pivot_element.row];
    }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Matrix& a, Column b) {
    size_t n = a.size();
    size_t m = a[0].size();

    std::vector <bool> used_columns(m, false);
    std::vector <bool> used_rows(n, false);
    for (int step = 0; step < n; ++step) {
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
  matrix newM(m, vector<double>(n, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      newM[j][i] = mx[i][j];
    }
  }
  return newM;
}


void printRow(const string name, const vector<double>& v) {
  cout << name << "-" << v.size() << ": ";
  for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
  cout << endl;
}

void print(const string name, const matrix &A) {
  int n = A.size();
  int m = A[0].size();
  cout << name << " " << n << "X" << m << endl;
  std::cout.precision(PRECISION);
  for (int i = 0; i < n; i++){
    cout << "[";
    for(int j = 0; j < m; j++) cout << A[i][j] << " ";
    cout << "]\n";
  }
}

// currently, only Y is calculated, which is not we expect
// we expect X (however, it's just a draft, we choose to forgive)
pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  // we need add extra rows to A and b, because all x cannot be negative
  // think about the following code, we know that the problem cannot be 
  // sloved by duality (complementary slackness)
  for(size_t i = 0; i < m; i++) {
    vector<double> tmp(m, 0);
    tmp[i] = -1;
    A.push_back(tmp);
    b.push_back(0);
  }
  // solve the dual equation
  print("A:", A);
  matrix dualA = transpose(n, m, A);
  print("dual of A:", dualA);
  printRow("c: ", c);
  vector<double> y = SolveEquation(dualA, c);
  print("dual of A:", dualA);
  printRow("y", y);
  cout << "solve_diet_problem 0" << endl;
  // check the result
  for(int i = 0; i < m && i < n; i++) {
    if(dualA[i][i]==0) {
      cout << "solve_diet_problem 1, i=" << i << endl;
      if (y[i]==0) return {1, vector<double>(m,0)};
      else return {-1, vector<double>(m,0)};
    }
  }
  cout << "solve_diet_problem 3, m="<< m << ", n=" << n << endl;
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
