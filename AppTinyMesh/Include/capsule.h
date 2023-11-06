#pragma once
#include "mathematics.h"
#include "node.h" 

class Capsule : public Noeud {
  public :
  Vector centre;
  Vector hauteur;
  float rayon;

  Capsule(const Vector& a,const Vector& b, float r) {
    centre= a;
    hauteur= b;
    rayon = r;
  }

  float Value(const Vector& p) override {
    Vector ba = hauteur;
    Vector pa = p;
    ba.operator-=(centre);
    pa.operator-=(centre);

    float baba = SquaredNorm(ba);
    float paba = SquaredNorm2(pa,ba);

    float h = Clamp(paba/baba,0.0,1.0);
    return Norm(pa-ba * h) - rayon; // capsule function distance
  }
};