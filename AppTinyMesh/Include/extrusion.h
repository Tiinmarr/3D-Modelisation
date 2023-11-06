#pragma once
#include "mathematics.h"
#include "node.h"

class Extrusion : public OperateurBinaire {
  public :
    Noeud* gauche;
    Noeud* droit;
    float rayon;

    Extrusion() {
    rayon= 0.0;
  }

    Extrusion(Noeud* g, Noeud* d, float k) {
    gauche= g;
    droit = d;
    rayon=k;
  }

  float Value(const Vector& p) override {
    float h = Math::Max(rayon-Math::Abs(gauche->Value(p) - droit->Value(p)), 0);
    return Math::Max(droit->Value(p),- gauche->Value(p)) + h * h * 0.25 / rayon;

  // float h = Math::Clamp( 0.5 + 0.5*(droit->Value(p)+gauche->Value(p))/k);
	// return Math::Mix( droit->Value(p), -gauche->Value(p), h ) + k*h*(1.0-h);
    }
};