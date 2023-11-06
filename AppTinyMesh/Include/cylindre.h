#pragma once
#include <math.h>
#include "mathematics.h"
#include "node.h" 

class Cylindre : public Noeud {
  public :
  Vector centre;
  Vector hauteur;
  float rayon;

  Cylindre(const Vector& a,const Vector& b, float r) {
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
    float x = Norm(pa*baba-ba*paba) - rayon*baba;
    float y;
    if (paba-baba*0.5>0){
      y=paba-baba*0.5-baba*0.5;
    }
    else {
      y=-(paba-baba*0.5)-baba*0.5;
    }   
    
    float x2 = x*x;
    float y2 = y*y*baba;
    
    float d = (Math::Max(x,y)<0.0)?-Math::Min(x2,y2):(((x>0.0)?x2:0.0)+((y>0.0)?y2:0.0));

    // if (d>0.0) {
    //   return sqrt(d)/baba;
    // }
    // else {
    //   return -sqrt(-d)/baba;
    // }
    return Math::Sign(d)*sqrt(Math::Abs(d))/baba;
  }
};