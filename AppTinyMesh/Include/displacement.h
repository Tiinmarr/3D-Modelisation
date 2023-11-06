#pragma once
#include "mathematics.h"
#include "node.h" 
#include <math.h>

class Displacement : public Noeud {
  public :
  Noeud* enfant;

  Displacement(Noeud* g) {
    enfant =g;
  }

  float Value(const Vector& p) override {
    float d1 = enfant->Value(p);
    float d2 = 0.2 * (0.5 * 0.5*sin(25.0*atan(p[0])*atan(p[2])*atan(p[1])));
    return d1 - d2;
  }
};