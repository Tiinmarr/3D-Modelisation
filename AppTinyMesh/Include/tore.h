#pragma once
#include "mathematics.h"
#include "node.h" 

class Tore : public Noeud {
  public :
  Vector param;
  float rayon;

  Tore(const Vector& c, float r) {
    param= c;
    rayon = r;
  }

  float Value(const Vector& p) override {
    Vector v=Vector(Norm2(p.operator[](0),p.operator[](2))-param.operator[](0),p.operator[](1),0);
    return Norm2(v.operator[](0),v.operator[](1)) - param.operator[](1); // tore function distance
  }
};