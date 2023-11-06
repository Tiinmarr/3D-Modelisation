#pragma once
#include "mathematics.h"
#include "node.h" 
#include <math.h>

class RoundCone : public Noeud {
  public :
  Vector v1;
  Vector v2;
  float r1, r2;

  RoundCone(const Vector& a,const Vector& b, float R1, float R2) {
    v1=a;
    v2=b;
    r1=R1;
    r2=R2;
  }

  float Value(const Vector& p) override {
    Vector ba = v2;
    ba.operator-=(v1);
    float l2 = SquaredNorm(ba);
    float rr = r1 - r2;
    float a2 = l2 - rr*rr;
    float il2 = 1.0/l2;

    Vector pa = p;
    pa.operator-=(v1);
    float y = SquaredNorm2(pa,ba);
    float z = y - l2;
    pa.operator*=(l2);
    ba.operator*=(y);
    pa.operator-=(ba);
    float x2 = SquaredNorm(pa);
    float y2 = y*y*l2;
    float z2 = z*z*l2;

    float k = Math::Sign(rr)*rr*rr*x2;
    if( Math::Sign(z)*a2*z2>k ) return  sqrt(x2 + z2) * il2 - r2;
    if( Math::Sign(y)*a2*y2<k ) return  sqrt(x2 + y2) * il2 - r1;
    return (sqrt(x2*a2*il2)+y*rr)*il2 - r1;
  }
};