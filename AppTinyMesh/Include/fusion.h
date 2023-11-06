#pragma once
#include <math.h>
#include "mathematics.h"
#include "node.h"

class Union : public OperateurBinaire {
  public :
    Noeud* gauche;
    Noeud* droit;
    float rayon;

    Union() {
    rayon= 0.0;
  }

    Union(Noeud* g, Noeud* d, float k) {
    gauche= g;
    droit = d;
    rayon = k;
  }

  float Value(const Vector& p) override {
    if (rayon==0.0){
      return Math::Min(droit->Value(p),gauche->Value(p));
    }    
    float h = Math::Max(rayon-Math::Abs(gauche->Value(p) - droit->Value(p)), 0);
    return Math::Min(droit->Value(p),gauche->Value(p)) - h * h * 0.25 / rayon;

    // on obtient un résultat qui s'apparent plus à l'extrusion smooth ici : 
    // float h = Math::Clamp( 0.5 + 0.5*(droit->Value(p)+gauche->Value(p))/rayon);
	  // return Math::Mix( droit->Value(p), -gauche->Value(p), h ) + rayon*h*(1.0-h);


    // Autre méthode vu en cours : 
    // return rayon * log(exp(-gauche->Value(p)/rayon) + exp(-droit->Value(p)/rayon));
    }
};