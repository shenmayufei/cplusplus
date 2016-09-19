#ifndef PANEL_H__
#define PANEL_H__

#include <set> // std::set
#include "shape.h"

// Panel is not used in main.cpp, 
// we need to use another design pattern to make it work correctly
// so just ignore it
class Panel {
private:
  std::set<Shape*> m_vShapes;
public:
  Panel(): m_vShapes(std::set<Shape*>()) {}
  void add(Shape* s) {
    m_vShapes.insert(s);
  }
  void remove(Shape* s) {
    m_vShapes.erase(s);
  }
};

#endif