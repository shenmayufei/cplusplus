#ifndef _NOT_EQUAL_TO_H__
#define _NOT_EQUAL_TO_H__

#include <algorithm>    // std::find_if
#include <functional>   // std::not_equal_to
#include <vector>


using std::vector;
using std::find_if;
using std::not_equal_to;
using std::bind;

template <typename T> 
vector<T> find_if_not_equal_to (const vector<T>& a) {
  vector<T> res;
  const T zero = T();
  typename vector<T>::const_iterator it = find_if (a.begin(), a.end(), bind(not_equal_to<T>(), std::placeholders::_1, zero));
  while(it != a.end()) {
    res.push_back(*it);
    it++;
    it = find_if (it, a.end(), bind(not_equal_to<T>(), std::placeholders::_1, zero));
  }
  return res;
}

#endif