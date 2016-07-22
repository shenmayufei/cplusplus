#ifndef __MY_RECTANGLE__
#define __MY_RECTANGLE__

#include <iostream>

class Shape
{                   
   int no;
};              
class Point{
  public:
   int x;
   int y;
   Point(int xx, int yy): x(xx), y(yy){};
};
class Rectangle: public Shape
{
private:
   int width;
   int height;
   Point * leftUp;
public:
   Rectangle(int width, int height, int x, int y);
   Rectangle(const Rectangle& other);
   Rectangle& operator=(const Rectangle& other);
   ~Rectangle();

   void print();
};

inline
Rectangle::Rectangle(int w, int h, int x, int y) : width(w), height(h) {
  leftUp = new Point(x, y);
}

inline 
Rectangle::Rectangle(const Rectangle& other) {
  this->width = other.width;
  this->height = other.height;
  this->leftUp = new Point(*other.leftUp);
}

inline 
Rectangle& Rectangle::operator=(const Rectangle& other) {
  this->width = other.width;
  this->height = other.height;
  delete this->leftUp;
  this->leftUp = new Point(*other.leftUp);
  return *this;
}

inline 
Rectangle::~Rectangle() {
  delete this->leftUp;
}

inline 
void Rectangle::print() {
  // std::cout << "left point addr: " << this->leftUp << std::endl;
  std::cout << "left up:(" << this->leftUp->x << ", " << this->leftUp->y << "), right bottom:(" << this->leftUp->x + this->width << ", " << this->leftUp->y + this->height << ")" << std::endl;
}
#endif
