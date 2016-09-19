#include <iostream>
#include "shapefactory.h"

int main(int argc, char* argv[]) {
  Shape* l = ShapeFactory::getShape(ShapeLine);
  l->draw();

  Shape* c = ShapeFactory::getShape(ShapeCircle);
  c->draw();

  Shape* r = ShapeFactory::getShape(ShapeRectangle);
  r->draw();
}