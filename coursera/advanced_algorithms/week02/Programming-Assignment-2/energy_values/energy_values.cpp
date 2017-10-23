/*
   g++ -o main energy_values.cpp -std=c++11
   ./main < tests/03
*/
#include <cmath>
#include <iostream>
#include <vector>

const double EPS = 1e-6;
const int PRECISION = 20;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(a, b);
}

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

Column SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    size_t n = a.size();
    if(n==0) return b;
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

void PrintColumn(const Column &column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        std::cout << column[row] << std::endl;
}

int main() {
    Equation equation = ReadEquation();
    Column solution = SolveEquation(equation);
    PrintColumn(solution);
    return 0;
}

