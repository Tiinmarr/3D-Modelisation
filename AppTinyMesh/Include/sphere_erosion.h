#pragma once
#include "mathematics.h"
#include "node.h" 

class Sphere_Erosion : public Noeud {
  public :
  Vector centre;
  float rayon;

  Sphere_Erosion(const Vector& c, float r) {
    centre= c;
    rayon = r;
  }

float sph( Vector i, Vector f, Vector c )
{
    // random radius at grid vertex i+c (please replace this hash by
    // something better if you plan to use this for a real application)
    double intpart;
    Vector  p = 17.0*Vector(modf(0.3183099*(i[0]+c[0])+0.11,&intpart),modf((i[1]+c[1])*0.3183099+ 0.17,&intpart),modf((i[2]+c[2])*0.3183099+0.13,&intpart));
    float w = modf(p[0]*p[1]*p[2]*(p[0]+p[1]+p[2]), &intpart);
    float r = 0.7*w*w;
    // distance to sphere at grid vertex i+c
    return Norm(f-c) - r; 
}
  float Value(const Vector& p) override {
  double intpart;
   Vector i = Vector(ceil(p[0]),ceil(p[1]),ceil(p[2]));
   Vector f =Vector(modf(p[0],&intpart),modf(p[1],&intpart),modf(p[2],&intpart));
   // distance to the 8 corners spheres
   return Math::Min(Math::Min(Math::Min(sph(i,f,Vector(-1.5,1.5,-1.5)),
                      sph(i,f,Vector(-1.5,1.5,1.5))),
                  Math::Min(sph(i,f,Vector(-1.5,-1.5,-1.5)),
                      sph(i,f,Vector(-1.5,-1.5,1.5)))),
              Math::Min(Math::Min(sph(i,f,Vector(1.5,-1.5,-1.5)),
                      sph(i,f,Vector(1.5,-1.5,1.5))),
                  Math::Min(sph(i,f,Vector(1.5,1.5,1.5)),
                      sph(i,f,Vector(1.5,1.5,-1.5)))));
}
};