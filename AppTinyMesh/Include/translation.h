#pragma once
#include "mathematics.h"
#include "node.h" 

class Translation : public Noeud {
  public :
  Noeud* enfant;
  Vector point;

  Translation(Noeud* g, const Vector& c) {
    point= c;
    enfant =g;
  }

  float Value(const Vector& p) override {
    Vector v=p;
    v.operator-=(point);
    return enfant->Value(v);
  }
};