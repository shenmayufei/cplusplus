#ifndef CIRCLE_H__
#define CIRCLE_H__

#include <iostream>
#include "shape.h"

// Circle defines the attributes of circle
class Circle : public Shape {
public:
  virtual void draw() { 
    // draw a circle 
    std::cout << "Circle::draw()\n";
  }
  virtual ~Circle(){
    // do some cleanup
  }
};

#endif