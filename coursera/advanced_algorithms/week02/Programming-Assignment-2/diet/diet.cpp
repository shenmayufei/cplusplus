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
 * Reference: https://en.wikipedia.org/wiki/Simplex_algorithm
 */


// helper functions
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

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

/********************************************* 
 * SolveEquation start
 *********************************************/

// SelectPivotElement selects the first free element
// the pivot value could be zero (which must be the first position)
// or non-zero value
// actually, column is still the row number (whose value is often not zero)
// the most ideal condition is row==column (whose value is not zero, probably one)
Position SelectPivotElement(
  const matrix &a, 
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
void SwapLines(matrix &a, vector<double> &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(matrix &a, vector<double> &b, const Position &pivot_element) {
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

vector<double> SolveEquation(matrix a, vector<double> b) {
    size_t n = a.size();
    size_t m = a[0].size();

    std::vector <bool> used_columns(m, false);
    std::vector <bool> used_rows(n, false);
    for (int step = 0; step < n; ++step) {
        Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }

    return b;
}
 /********************************************* 
 * SolveEquation end
 *********************************************/

/********************************************* 
 * SimplexSolve start
 *********************************************/

// SimplexSelectPivotElement selects the first free element
Position SimplexSelectPivotElement(
  const matrix &a, 
  const vector<double>& b,
  vector<bool> &used_rows, 
  vector<bool> &used_columns) {
    size_t n = used_rows.size();
    size_t m = used_columns.size();

    size_t p_row = 0;
    size_t p_col = 0;

    // select column (coefficient is negative, and not used yet)
    for(size_t i = 1; i < m; i++) {
      if (a[0][i] >= 0) continue; // not satisfactory
      if (used_columns[i]) continue;  // satisfactory, but meet loop
      p_col = i;
      break;
    }

    // select row (which is most easily overflowed as the variable increases)
    double min_div = numeric_limits<double>::max();
    for(size_t i = 1; i < n; i++) {
      if (a[i][p_col] <= 0 || b[i] < 0) continue;  // not satisfactory
      if (used_rows[i]) continue;  // meet loop
      if (b[i] == 0) return Position(p_col, i);
      double tmp = b[i] / a[i][p_col];
      if (tmp < min_div) {
        min_div = tmp;
        p_row = i;
      }
    }

    return Position(p_col, p_row);
}

void SimplexProcessPivotElement(matrix &a, vector<double> &b, const Position &pivot_element) {
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
        for(size_t j = 0; j < m; j++)
            a[i][j] -= multBy * a[pivot_element.row][j];
        b[i] -= multBy * b[pivot_element.row];
    }
}

void SimplexSolve(matrix& A, vector<double>& b) {
    size_t n = A.size();
    size_t m = A[0].size();

    vector<bool> used_columns(m, false);
    vector<bool> used_rows(n, false);
    used_columns[0] = true;
    used_rows[0] = true;

    size_t count = 0;
    while(true) {
      cout << "round " << ++count << ":" << endl;
      print(" A:", A);
      printRow("new b: ", b);
      Position pivot_element = SimplexSelectPivotElement(A, b, used_rows, used_columns);
      if(pivot_element.column==0) break;  // terminate: all coefficients are nonnegative or meet loop
      if(pivot_element.row==0) break; // terminate: no positive coefficients for the rest rows (unbounded value) or meet loop

      SimplexProcessPivotElement(A, b, pivot_element);
    }
}

/********************************************* 
 * SimplexSolve end
 *********************************************/

// here we use simplex algorithm to solve the problem
pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  /*** expand A and b, c as the first row of the new A **/
  /*** start expanding ***/
  int newN = n+1;
  int newM = m + n + 1;
  matrix newA(newN, vector<double>(newM, 0));
  // set c as the first row of newA
  vector<double>& firstRow = newA[0];
  firstRow[0] = 1;
  for(size_t i = 0; i < m; i++) firstRow[i+1] = - c[i];
  // set next n rows according to A
  for(size_t i = 0; i < n; i++) {
    for(size_t j = 0; j < m; j++)  newA[i+1][j+1] = A[i][j];
    newA[i+1][m+i+1] = 1;
  }
  // set newB
  vector<double> newB(newN, 0);
  for(size_t i = 0; i < n; i++) newB[i+1] = b[i];
  /*** end expanding ***/

  // use Guassian elimination to find replace all variables whose coefficient is negative (because we want the maximum)
  SimplexSolve(newA, newB);

  // check the results
  bool all_non_negative = true;
  size_t negative_idx = 0;
  for(size_t i = 0; i < newM; i++) {
    if (newA[0][i] < 0) {
      all_non_negative = false;
      break;
    }
  }
  if (all_non_negative) {
    // solve the equation
    // @todo: the SolveEquation cannot handle when a col is all ZERO, I need to fix the bug
    for(size_t j = 1; j < newM; j++) {
      if(newA[0][j] > 0) {
        for(size_t i = 0; i < newN; i++) newA[i][j] = 0; // set the coefficients as ZERO
        vector<double> resSet = SolveEquation(newA, newB);
        print("new A:", newA);
        printRow("new res:", resSet);
        vector<double> res(m, 0);
        for(size_t i = 0; i < m; i++) res[i] = resSet[i+1];
        return {1, res};
      }
    }
  } else {
    // @todo: other case, need checking
  }
  return {1, vector<double>(m,0)};
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
