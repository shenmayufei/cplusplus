#ifndef SHAPE_H__
#define SHAPE_H__

// Shape defines the interface of Shapes
class Shape {
public:
  virtual void draw() {}
  virtual ~Shape(){}
};

enum ShapeType { ShapeLine = 1, ShapeCircle, ShapeRectangle };

#endif