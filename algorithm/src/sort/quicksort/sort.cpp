#include<iostream>

void printIntArrary(int src[], int size) {
  for (int i = 0; i < size-1; i++) {
    std::cout << src[i] << ", ";
  }
  std::cout << src[size-1] << std::endl;
}


// first element as pivot
void quicksort(int src[], int start, int end) {
  // zero or one item
  if (start>=end) return;

  // two items
  if (start+1 == end) {
    if (src[start] <= src[end]) return;
    int temp = src[start];
    src[start] = src[end];
    src[end] = temp;
    return;
  }

  int pivot = start;
  int pivotVal = src[start];
  int i = start+1, j=end;
  for (; i <= j; i++,j--) {
    while(src[i]<pivotVal && i <= end) i++;
    while(src[j]>pivotVal && pivot <= j) j--;

    // printIntArrary(src, 7);
    // std::cout << "start=" << start << ", end=" << end << ", i=" << i << ",j=" << j << std::endl << std::endl;
    if (i > end) {
      src[pivot] = src[end];
      src[end] = pivotVal;
      quicksort(src, pivot, end-1);
      break;
    } 
    if (i == end) {
      src[pivot] = src[end-1];
      src[end-1] = pivotVal;
      quicksort(src, pivot, end-2);
      break;
    }
    if (j == pivot) {
      quicksort(src, pivot+1, end);
      break;
    }

    if (i == j) {
      src[pivot] = src[i-1];
      src[i-1] = pivotVal;
      quicksort(src, start, i-2);
      quicksort(src, i+1, end);
      break;
    }

    if (i > j) {
      src[pivot] = src[j];
      src[j] = pivotVal;
      quicksort(src, start, j-1);
      quicksort(src, j+1, end);
      break;
    }

    // exchage the values on the two locations
    int temp = src[i];
    src[i] = src[j];
    src[j] = temp;
  }
  // std::cout << "--after a round of sort, start="<< start << ", end = "<< end << ", i = " << i << ", j=" << j << std::endl;
  // printIntArrary(src, 7);
  if (i == j) {
    if (src[i] < pivotVal) {
      src[pivot] = src[i];
      src[i] = pivotVal;
    }
    // std::cout << "--after change, i==j branch start="<<start<<", end="<<end <<",i = " << i << ", j=" << j << std::endl;
    // printIntArrary(src, 7);
    quicksort(src, start, i-1);
    quicksort(src, i+1, end);
  } else {
    if (src[j] < pivotVal) {
      src[pivot] = src[j];
      src[j] = pivotVal;
    }
    // std::cout << "--after change,i!=j branch start="<<start<<", end="<<end <<",i = " << i << ", j=" << j << std::endl;
    // printIntArrary(src, 7);
    quicksort(src, start, j-1);
    quicksort(src, j+1, end);
  }
}

bool testSeven() {
  const int m = 7, n = 20;
  int shouldSuccess[n][m] = {
    {1,2,3,4,5,6,7},
    {1,2,3,4,5,6,7},
    
    {7,6,5,4,3,2,1},
    {1,2,3,4,5,6,7},

    {0,7,0,7,0,7,0},
    {0,0,0,0,7,7,7},

    {7,0,7,0,7,0,7},
    {0,0,0,7,7,7,7},

    {1,3,5,7,2,4,6},
    {1,2,3,4,5,6,7},

    {6,4,2,7,5,3,1},
    {1,2,3,4,5,6,7},

    {1,1,4,4,4,1,1},
    {1,1,1,1,4,4,4},

    {1,2,3,1,2,3,1},
    {1,1,1,2,2,3,3},

    {6,7,8,9,1,2,3},
    {1,2,3,6,7,8,9},
    
    {7,4,5,3,8,9,6},
    {3,4,5,6,7,8,9}
  };

  for (int i = 0; i < n; i+=2) {
    quicksort(shouldSuccess[i], 0, m-1);
  }

  for (int i = 0; i < n; i+=2) {
    for (int j = 0; j < m; j++) {
      if(shouldSuccess[i][j] != shouldSuccess[i+1][j]) {
        std::cout << "i:" << i << ", j:"<< j <<", shouldSuccess[i][j] should be " << shouldSuccess[i+1][j] << ", but is " << shouldSuccess[i][j] << std::endl;
        return false;
      }
    }
  }
  return true;
}

bool testZero() {
  const int m = 0, n = 2;
  int shouldSuccess[n][m] = {{},{}};

  for (int i = 0; i < n; i+=2) {
    quicksort(shouldSuccess[i], 0, m-1);
  }

  for (int i = 0; i < n; i+=2) {
    for (int j = 0; j < m; j++) {
      if(shouldSuccess[i][j] != shouldSuccess[i+1][j]) {
        std::cout << "i:" << i << ", j:"<< j <<", shouldSuccess[i][j] should be " << shouldSuccess[i+1][j] << ", but is " << shouldSuccess[i][j] << std::endl;
        return false;
      }
    }
  }
  return true;
}

bool testOne() {
  const int m = 1, n = 2;
  int shouldSuccess[n][m] = {
    {1},
    {1}
  };

  for (int i = 0; i < n; i+=2) {
    quicksort(shouldSuccess[i], 0, m-1);
  }

  for (int i = 0; i < n; i+=2) {
    for (int j = 0; j < m; j++) {
      if(shouldSuccess[i][j] != shouldSuccess[i+1][j]) {
        std::cout << "i:" << i << ", j:"<< j <<", shouldSuccess[i][j] should be " << shouldSuccess[i+1][j] << ", but is " << shouldSuccess[i][j] << std::endl;
        return false;
      }
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (testZero()) {
    std::cout << "test zero length array passed" << std::endl;
  }

  if (testOne()) {
    std::cout << "test one length array passed" << std::endl;
  }

  if (testSeven()) {
    std::cout << "test seven length array passed" << std::endl;
  }
}