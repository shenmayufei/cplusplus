#ifndef LINE_H__
#define LINE_H__

#include "shape.h"

// Line defines the attributes of line
class Line : public Shape {
public:
  virtual void draw() { 
    // draw the line 
    std::cout << "Line::draw()\n";
  }
  virtual ~Line(){
    // do some cleanup
  }
};

#endif