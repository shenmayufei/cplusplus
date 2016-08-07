#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;

int testOptimal() ;

double get_optimal_value_slow(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  while(capacity > 0) {
    // select biggest one
    int idx = 0;
    double maxAverage = double(values[0]) / weights[0]; 
    for(int i = 1; i < values.size() ; i++) {
      double thisAvg = (double)values[i] / weights[i];
      if(maxAverage < thisAvg ) {
        maxAverage =  thisAvg;
        idx = i;
      } 
    }

    if (weights[idx] >= capacity) {
      value += maxAverage * capacity;
      return value;
    }

    value += values[idx];
    capacity -=  weights[idx];

    weights[idx] = weights.back();
    values[idx] = values.back();
    int arrSize = weights.size();
    weights.resize(arrSize-1);
    values.resize(arrSize-1);
  }
  return value;
}

vector<int> SortByAverage(vector<int> weights, vector<int> values) {
  int arrLen = weights.size();
  // sort by value per weight (value/weight)
  // averages is used for sorting
  vector<double> averages;
  vector<int> indexes;
  averages.reserve(arrLen);
  indexes.reserve(arrLen);

  for(int i = 0; i  < arrLen; i++) {
    double avg = (double)values[i] / weights[i];
    if (averages.size() == 0 || avg >= averages.back()) {
      averages.push_back(avg);
      indexes.push_back(i);
      continue;
    }


    int j = averages.size() -1;
    averages.push_back(averages[j]);  // increment size by 1
    indexes.push_back(indexes[j]);
    for(; j > 0 && averages[j-1] > avg; j--) {
      averages[j] = averages[j-1];
      indexes[j] = indexes[j-1];
    }
    indexes[j] = i;
    averages[j] = avg;
  }
  return indexes;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  int arrLen = weights.size();

  vector<int> indexes = SortByAverage(weights, values);
  // select from the larget value/wight
  double value = 0.0;
  for(int j = arrLen-1; j>=0 ; j--) {
    int idx = indexes[j];
    if (weights[idx] >= capacity) {
      value += (double)values[idx] / weights[idx] * capacity;
      return value;
    }

    value += values[idx];
    capacity -= weights[idx];
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout << std::fixed << std::setprecision(4) << optimal_value << std::endl;

  return 0;
}


// int testOptimal()  {
//   while(true) {
//     int arrSize = rand() % 5 + 2;
//     vector<int> weights;
//     vector<int> values;
//     for (int i = 0; i < arrSize; i++) {
//       weights.push_back(rand() % 5 + 1);
//       values.push_back(rand() % 100 + 10);
//     }

//     vector<int> indexes = SortByAverage(weights, values);
    
//   }
// }

int testSort() {
  while(true) {
    int arrSize = rand() % 5 + 2;
    vector<int> weights;
    vector<int> values;
    for (int i = 0; i < arrSize; i++) {
      weights.push_back(rand() % 5 + 1);
      values.push_back(rand() % 40 + 10);
    }

    vector<int> indexes = SortByAverage(weights, values);
    
  }
}
