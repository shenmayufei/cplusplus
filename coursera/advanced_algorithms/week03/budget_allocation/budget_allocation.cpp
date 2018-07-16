#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n)
    {}

    // generateConditionsAllMax: generate condition, if sum of all max > b
    vector<vector<int> > generateConditionsAllMax(const vector<int>& ids, const vector<int>& max, const int b) {
      vector<vector<int> > result;

      // check all max
      int total = accumulate(max.begin(), max.end(), 0);
      if (total > b) { // formula is not satisified
        vector<int> row;
        for(int i= 0; i < max.size(); i++) {
          int ele = max[i] > 0? -ids[i]-1: ids[i] + 1;
          row.push_back(ele);
        }

        result.push_back(row);
      }
      return result;
    }

    // generateConditionsOneMin: generate condition, if sum of all max but one min > b
    vector<vector<int> > generateConditionsOneMin(const vector<int>& ids, const vector<int>& max, const vector<int>& min, const int b) {
      vector<vector<int> > result;

      if (max.size() < 2) return result;

      for(int i = 0; i < max.size(); i++) {
        int newb = b - min[i];
        vector<int> newids;
        vector<int> newmax;
        for(int j = 0; j < max.size(); j++) {
          if (i == j) continue;
          newids.push_back(ids[j]);
          newmax.push_back(max[j]);  
        }
        vector<vector<int> > res = generateConditionsAllMax(newids, newmax, newb);
        for(auto vec : res) result.push_back(vec);
      }

      return result;
    }

    // generateConditionsTwoMin: generate condition, if sum of all max but two min > b
    vector<vector<int> > generateConditionsTwoMin(const vector<int>& ids, const vector<int>& max, const vector<int>& min, const int b) {
      vector<vector<int> > result;

      if (max.size() < 3) return result;

      for(int i = 0; i < max.size() -1 ; i++) {
        for(int j = i + 1; j< max.size(); j++) {
          int newb = b - min[i] - min[j];
          vector<int> newids;
          vector<int> newmax;
          for(int k = 0; k < max.size(); k++) {
            if (i == k || j == k) continue;
            newids.push_back(ids[k]);
            newmax.push_back(max[k]);  
          }
          vector<vector<int> > res = generateConditionsAllMax(newids, newmax, newb);
          for(auto vec : res) result.push_back(vec);
        }
      }

      return result;
    }

    vector<vector<int> > generateConditions(const vector<int>& ids, const vector<int>& coefficients, const int b) {
      vector<vector<int> > result;

      if (ids.size() == 0) return result;

      vector<int> max(coefficients.size(), 0);
      vector<int> min(coefficients.size(), 0);
      for(int i = 0; i < coefficients.size(); i++) {
        if (coefficients[i] > 0) max[i] = coefficients[i];
        else min[i] = -coefficients[i];
      }

      // handle data size is one
      if (ids.size() == 1) {
          vector<vector<int> > res = generateConditionsAllMax(ids, max, b);
          for(auto vec : res) result.push_back(vec);
          return result;
      }

      // check all max
      if (ids.size() == 2) {
        // all max
        vector<vector<int> > res = generateConditionsAllMax(ids, max, b);
        for(auto vec : res) result.push_back(vec);
        // one min
        res = generateConditionsOneMin(ids, max, min, b);
        for(auto vec : res) result.push_back(vec);
      }

      // check max of sum of any two variables compared with b
      if (ids.size() == 3) {
        // all max
        vector<vector<int> > res = generateConditionsAllMax(ids, max, b);
        for(auto vec : res) result.push_back(vec);
        // one min
        res = generateConditionsOneMin(ids, max, min, b);
        for(auto vec : res) result.push_back(vec);
        // two min
        res = generateConditionsTwoMin(ids, max, min, b);
        for(auto vec : res) result.push_back(vec);
      }
      return result;
    }

    void printEquisatisfiableSatFormula() {
      // Solution: find all falsified combinations of <xi, xj, xk, b>
      vector<vector<int> > formulas;
      for(int i = 0; i < A.size(); i++) {
          vector<int>& ai = A[i];
          int bi = b[i];

          vector<int> ids;
          vector<int> coefficients;
          for(int j = 0; j < ai.size(); j++) {
            if (ai[j] != 0) {
              ids.push_back(j);
              coefficients.push_back(ai[j]);
            }
          }
          auto res = generateConditions(ids, coefficients, bi);
          formulas.insert(formulas.end(), res.begin(), res.end());
      }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;  // n formulas, m variables
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> converter.A[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
