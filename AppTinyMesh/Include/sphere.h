#pragma once
#include "mathematics.h"
#include "node.h" 

class Sphere : public Noeud {
  public :
  Vector centre;
  float rayon;

  Sphere() {
    centre = Vector(0.0, 0.0, 0.0);
    rayon = (1.0);
  }

  Sphere(const Vector& c, float r) {
    centre= c;
    rayon = r;
  }

  float Value(const Vector& p) override {
    Vector v=centre;
    v -= p;
    return Norm(v) - rayon; // sphere function distance
  }
};