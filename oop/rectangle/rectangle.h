#ifndef __MY_RECTANGLE__
#define __MY_RECTANGLE__

#include <iostream>

class Shape
{                   
   int no;
public:
  Shape(): no(0) {}
  Shape(const Shape& o): no(o.no) { }
  Shape& operator=(const Shape& o) { no = o.no; return *this; };
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

   void print() const;
};

inline
Rectangle::Rectangle(int w, int h, int x, int y) : width(w), height(h) {
  leftUp = new Point(x, y);
}

inline 
Rectangle::Rectangle(const Rectangle& other): Shape(other), width(other.width), height(other.height) {
  if (other.leftUp != nullptr) this->leftUp = new Point(*other.leftUp);
}

inline 
Rectangle& Rectangle::operator=(const Rectangle& other) {
  if (this == &other) return *this;

  Shape::operator=(other);
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
void Rectangle::print() const {
  // std::cout << "left point addr: " << this->leftUp << std::endl;
  std::cout << "left up:(" << this->leftUp->x << ", " << this->leftUp->y << "), right bottom:(" << this->leftUp->x + this->width << ", " << this->leftUp->y + this->height << ")" << std::endl;
}
#endif
