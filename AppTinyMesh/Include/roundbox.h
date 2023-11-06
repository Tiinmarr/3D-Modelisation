#pragma once
#include "mathematics.h"
#include "node.h" 

class RoundBox : public Noeud {
  public :
  Vector centre;
  float rayon;

  RoundBox(const Vector& c, float r) {
    centre= c;
    rayon = r;
  }

  float Value(const Vector& p) override {
    Vector d = Abs(p);
    d.operator-=(centre);
    return Norm(Vector::Max(d,Vector(0.0,0.0,0.0))) + Math::Min(Math::Max(d[0],Math::Max(d[1],d[2])),0.0) - rayon; // roundbox function distance
  }
};