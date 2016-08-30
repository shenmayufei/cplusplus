#ifndef __MY_NUMERIC_LIMITS_H_
#define __MY_NUMERIC_LIMITS_H_


template <typename T>
struct Calculator {
    static constexpr bool is_specialized = false;
};

template<> 
struct Calculator<int> {
  static constexpr bool is_specialized = true;
  static int GetLimit() { return 100; }
};

template<> 
struct Calculator<long> {
  static constexpr bool is_specialized = true;
  static long GetLimit() { return 1000; }
};

template<> 
struct Calculator<float> {
  static constexpr bool is_specialized = true;
  static float GetLimit() { return 999.99; }
};

template<>
struct Calculator<double> {
  static constexpr bool is_specialized = true;
  static double GetLimit() { return 888.8888888; }
};

#endif