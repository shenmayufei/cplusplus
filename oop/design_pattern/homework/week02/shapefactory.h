#ifndef SHAPE_FACTORY_H__
#define SHAPE_FACTORY_H__

#include "shape.h"
#include "line.h"
#include "circle.h" 
#include "rec.h" 

// 使用 ShapeFactory 创建新的形状（工厂模式）
class ShapeFactory {
public:
   //use getShape method to get object of type shape 
   static Shape* getShape(ShapeType st){
     if (st == ShapeLine) return new Line();
     if (st == ShapeCircle) return new Circle();
     if (st == ShapeRectangle) return new Rectangle();
     return nullptr;
   }
};

#endif