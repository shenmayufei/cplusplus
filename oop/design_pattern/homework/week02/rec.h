#ifndef RECTANGLE_H__
#define RECTANGLE_H__

#include "shape.h"

// Rectangle defines the attributes of rectangle
class Rectangle : public Shape {
public:
  virtual void draw() { 
    // draw a rectangle 
    std::cout << "Rectangle::draw()\n";
  }
  virtual ~Rectangle(){
    // do some cleanup
  }
};

#endif