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
 * 
 * Phase I: find a feasible solution of the original prolem, according to extended problem
 * Phase II: find the basic feasible solution
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


void printAb(const string name, const matrix &A, const vector<double>& b) {
  int n = A.size();
  int m = A[0].size();
  cout << name << " " << n << "X" << m << endl;
  std::cout.precision(PRECISION);
  for (int i = 0; i < n; i++){
    cout << "[";
    for(int j = 0; j < m; j++) cout << A[i][j] << " ";
    cout << "] " << b[i] << "\n";
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

// SelectPivotElement selects the first free line and first free element
// the pivot value could be zero (which must be the first position)
// or non-zero value
// actually, column is still the row number (whose value is often not zero)
// the most ideal condition is row==column (whose value is not zero, probably one)
pair<int, Position> SelectPivotElement(
  const matrix &a, 
  std::vector <bool> &used_rows, 
  std::vector <bool> &used_columns) {
    size_t n = used_rows.size();
    size_t m = used_columns.size();

    size_t r = 0;
    size_t c = 0;
    while(used_rows[r] && r < n) r++;  // find the next row not used
    while(used_columns[c] && c < m) c++;

    if (r == n) return {r, Position(0,0)};

    for(size_t j = c; j < m; j++) {
      for(size_t i = r; i < n; i++) {
        if (a[i][j] != 0) {
          return {r, Position(j, i)};
        }
      }
      used_columns[j] = true;
    }

    return {r, Position(n, r)};
}

// After swapping, row==column
// the first free element could probably NOT zero, but also possibly is zero
void SwapLines(matrix &a, vector<double> &b, int r, Position &pivot_element) {
  std::swap(a[r], a[pivot_element.row]);
  std::swap(b[r], b[pivot_element.row]);
  pivot_element.row = r;
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

void SolveEquation(matrix& a, vector<double>& b) {
    size_t n = a.size();
    size_t m = a[0].size();

    std::vector <bool> used_columns(m, false);
    std::vector <bool> used_rows(n, false);
    for (int step = 0; step < m && step < n; ++step) {
        auto pvPair = SelectPivotElement(a, used_rows, used_columns);
        int r = pvPair.first;
        Position pivot_element = pvPair.second;
        if (r == n || pivot_element.column == m) return;  // 
        SwapLines(a, b, r, pivot_element);

        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);

        // cout << "SolveEquation step " << step << endl;
        // printAb("A b:", a, b);
    }
}
 /********************************************* 
 * SolveEquation end
 *********************************************/

/********************************************* 
 * SimplexSolve start
 *********************************************/

// SimplexSelectPivotElement selects the first free element
Position SimplexSelectPivotElement(
  int n,
  int m,
  const matrix &a, 
  const vector<double>& b,
  size_t row_start) {
    bool found = false;
    size_t p_row = 0;
    size_t p_col = 0;

    // select column (coefficient is negative, and most negetive)
    for(size_t i = row_start; i < m; i++) {
      if (a[0][i] >= 0) continue; // not satisfactory
      if (!found){ 
        p_col = i;
        found = true;
      } else {
        if(a[0][i] < a[0][p_col]) p_col = i;
      }
    }

    // select row (which is most easily overflowed as the variable increases)
    double min_div = numeric_limits<double>::max();
    for(size_t i = row_start; i < n; i++) {
      if (a[i][p_col] <= 0) continue;  // not satisfactory
      if (b[i] < -0.001) continue;  // allow degeneration (ZERO)
      double tmp = b[i] / a[i][p_col];
      if (tmp < min_div) {
        min_div = tmp;
        p_row = i;
      }
    }

    return Position(p_col, p_row);
}

// feasible or infeasible
bool SimplexProcessPivotElement(matrix &a, vector<double> &b, const Position &pivot_element, size_t row_start) {
    if (a[pivot_element.row][pivot_element.column] == 0) return true;
    size_t n = a.size();
    size_t m = a[0].size();

    // set this row pivot value as ONE
    double baseVal = a[pivot_element.row][pivot_element.column];
    for(size_t j = 0; j< m; j++) a[pivot_element.row][j] /= baseVal;
    b[pivot_element.row] /= baseVal;

    // update other rows
    for(size_t i = 0; i < n; i++){
        if (i==pivot_element.row) continue;
        if (a[i][pivot_element.column] < 0.001 && a[i][pivot_element.column] > -0.001) continue;
        double multBy = a[i][pivot_element.column];
        
        // update values
        for(size_t j = 0; j < m; j++)
          a[i][j] -= multBy * a[pivot_element.row][j];
         
        b[i] -= multBy * b[pivot_element.row];
    }

    return true;
}

// -1, infeasible, no solution
// 0, bounded solution
// 1, infinity
int SimplexSolve(matrix& A, vector<double>& b, size_t row_start) {
    size_t n = A.size();
    size_t m = A[0].size();

    size_t count = 0;
    while(true) {
      // check feasibility
      for(size_t i = row_start; i< n; i++ ){
        bool no_negative = true;
        bool no_positive = true;
        for(size_t j = 0; j < m; j++){
          if(A[i][j] >= 0.001) no_positive = false;  // exist some positive
          else if(A[i][j] <= -0.001) no_negative = false; // exist some negative, namely not positve
        }
        if(b[i] >= 0.001 && no_positive) {
          // cout << "no positive, i=" << i << endl;
          return false; // infeasible
        }
        if(b[i] <= -0.001 && no_negative) {
          // cout << "no negative" << endl;
          return false; // infeasible
        }
      }
      
      Position pivot_element = SimplexSelectPivotElement(n, m, A, b, row_start);
      if(pivot_element.column==0) return 0;  // terminate: all coefficients are nonnegative or meet loop
      if(pivot_element.row==0) return 1; // terminate: no positive coefficients for the rest rows -> infinity

      cout << "SimplexSolve round " << ++count << ":" << endl;
      printAb(" A b:", A, b);
      cout << "......., row:" << pivot_element.row << ", col:" << pivot_element.column << ", val:" << A[pivot_element.row][pivot_element.column] << endl;
      bool feasible = SimplexProcessPivotElement(A, b, pivot_element, row_start);
      cout << "feasible: " << feasible << endl;
      cout << endl << endl;
      if (!feasible) return -1;
    }

    // final check: check feasibility
    for(size_t i = row_start; i< n; i++ ){
      bool no_negative = true;
      bool no_positive = true;
      for(size_t j = 0; j < m; j++){
        if(A[i][j] >= 0.001) no_positive = false;  // exist some positive
        else if(A[i][j] <= -0.001) no_negative = false; // exist some negative, namely not positve
      }
      if(b[i] >= 0.001 && no_positive) {
        cout << "no positive, i=" << i << endl;
        return false; // infeasible
      }
      if(b[i] <= -0.001 && no_negative) {
        cout << "no negative" << endl;
        return false; // infeasible
      }
    }

    return 0;
}

/********************************************* 
 * SimplexSolve end
 *********************************************/

pair<matrix, vector<double> > solve_phase_i(
  int n,
  int m,
  matrix A,
  vector<double> b,
  vector<double> c){
    bool needPhaseI = false;
    for(size_t i = 0; i < n; i++) needPhaseI = needPhaseI || (b[i] < 0);
  
    if (!needPhaseI) {
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
      return make_pair(newA, newB);
    }

    // need Phase I
    // continue expanding
    int newN = n+2;
    int newM = m + 2 * n + 2;
    matrix newA(newN, vector<double>(newM, 0));
    vector<double> newB(newN, 0);

    // first row consists of artifical variables, 
    // which should not enter the basis
    // Z = -a1 - a2 - a3 ... - aN; find its max for this problem.
    vector<double>& firstRow = newA[0]; 
    firstRow[0] = 1;
    for(size_t j = 2 + m + n; j < newM; j++) firstRow[j] = 1;
    
    // the second row consists of original coefficients
    // we want to find its max
    vector<double>& secondRow = newA[1];
    secondRow[1] = 1;
    for(size_t i = 0; i < m; i++) secondRow[i+2] = -c[i];

    // the next rows are the coefficents from A
    for(size_t i = 0; i < n; i++) {
      vector<double>& r = newA[i+2];
      // set the first m coefficients
      for(size_t j = 0; j < m; j++) {
        if (b[i] < 0) r[j+2] = - A[i][j];
        else r[j+2] = A[i][j];
      }
      // set the slack variable
      if (b[i] < 0) r[2+m+i] = -1;
      else r[2+m+i] = 1;
      // set the artificial variable
      r[2 + m + n + i] = 1;
      // set new b
      if (b[i] < 0) newB[i+2] = - b[i];
      else newB[i+2] = b[i];
    }

    // price out the artificial variables in the first row
    for(size_t i = 0; i < n; i++) {
      for(size_t j = 0; j < newM; j++) {
        newA[0][j] -= newA[2+i][j];
      }
      newB[0] -= newB[2+i];
    }

    cout << "Phase I, after pricing out:" << endl;
    printAb("A, b:", newA, newB);

    // solve the phase I problem
    SimplexSolve(newA, newB, newB.size() - n);
    cout << "Phase I, after solve:" << endl;
    printAb("A, b:", newA, newB);

    // remove artificial variables in newA and newB
    int newN2 = n+1;
    int newM2 = 1 + m + n;
    matrix newA2(newN2, vector<double>(newM2, 0));
    for(size_t i = 0; i < newN2; i++) {
      for(size_t j = 0; j < newM2; j++) {
        newA2[i][j] = newA[i+1][j+1];
      }
    }
    vector<double> newB2(newB.begin()+1, newB.end());

    return make_pair(newA2, newB2);
}

// here we use simplex algorithm to solve the problem
// m variables and n constraits
pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  pair<matrix, vector<double> > res = solve_phase_i(n, m, A, b, c);
  matrix newA = res.first;
  vector<double> newB = res.second;
  printAb("phase I result: ", newA, newB);
  cout << "newB.size()-n=" << newB.size() -n  << ", n=" << n << endl << endl; 
  int ret_code = SimplexSolve(newA, newB, newB.size() - n);
  printAb("phase II result: ", newA, newB);
  cout << "newB.size()-n=" << newB.size() -n  << ", n=" << n << endl; 
  if (ret_code != 0) return {ret_code, newB}; // fix infinity problem (tests/03)
  
  cout << endl;
  printAb("phase II result:", newA, newB);

  // solve the equation
  // there ever had a bug here, because I write A[0] instead of newA[0]
  size_t newM = newA[0].size();
  for(size_t j = 1; j < newM; j++) {
    vector<double> tmp(newM, 0);
    if(newA[0][j] > 0) {
        newA[0][j] = 0;
        tmp[j] = 1;
    }
    newA.push_back(tmp);
    newB.push_back(0);
  }
  // print("new A:", newA);
  // printRow("new B:", newB);

  // if any element in c is zero, the unknown value is set as ZERO as the optimal
  // check test/07
  for(size_t i = 0; i < m; i++) {
    if (c[i] == 0) {
      vector<double> tmp(newM, 0);
      tmp[i+1] = 1;
      newA.push_back(tmp);
      newB.push_back(0);
    }
  }

  // cout << "before solve equation" << endl << endl;
  SolveEquation(newA, newB);
  // fix the bug for tests/02
  for(size_t i = 1; i < newB.size(); i++) {
    if (newB[i] < -0.001) return {-1, vector<double>(m, 0)};
  }
  // cout << "after solve equation" << endl << endl;
  // print("new A:", newA);
  // printRow("new res:", newB);
  vector<double> resVec(m, 0);
  for(size_t i = 0; i < m; i++) {
    // expected form: canonical form
    // every unknown variable is known
    // every unknown variable is >= 0; otherwise no solution
    if (newB[i+1] < -0.001) return {-1, resVec};
    resVec[i] = newB[i+1];
  }
  // printRow("solution: ", resVec);
  return {0, resVec};
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
