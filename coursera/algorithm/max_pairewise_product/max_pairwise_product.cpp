#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

long long int MaxPairwiseProduct(const vector<long long int>& numbers) {
  int n = numbers.size();
  if (n<2) return 0;
  if (n==2) return numbers[0] * numbers[1];
  long long int biggest, bigger;
  if (numbers[0] > numbers[1]) {
    biggest = numbers[0];
    bigger = numbers[1];
  } else {
    biggest = numbers[1];
    bigger = numbers[0];
  }

  for (int i = 2; i < n; ++i) {
    long long tmp = numbers[i];
    if (tmp <= bigger) continue;

    if (tmp >= biggest) {
      bigger = biggest;
      biggest = tmp;
    } else {
      bigger = tmp;
    }
  }
  return bigger * biggest;
}

int main() {
    int n;
    cin >> n;
    vector<long long int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    long long int result = MaxPairwiseProduct(numbers);
    cout << result << "\n";
    return 0;
}
