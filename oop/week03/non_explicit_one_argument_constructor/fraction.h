#ifndef __MY_FRACTION__
#define __MY_FRACTION__

#include<iostream>

using std::ostream;

class Fraction {
  public:
    Fraction(int num, int den=1): m_numerator(num), m_denominator(den){};
    Fraction operator+(const Fraction& f) {return Fraction(f.m_numerator, f.m_denominator); };

    friend ostream& operator << (ostream& os, const Fraction& f);
  private:
    int m_numerator;
    int m_denominator;
};

ostream& operator<<(ostream& os, const Fraction& f) {
  return os << f.m_numerator << "/" << f.m_denominator;
}

#endif