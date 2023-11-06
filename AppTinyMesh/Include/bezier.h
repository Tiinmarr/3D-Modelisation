#pragma once
#include <vector>
#include <math.h>
#include "mathematics.h"
#include "node.h"
#include "mesh.h"


class Array2 {
  protected:
  int rows;
  int columns;
  std::vector<Vector> data;

  public:
    Array2() : rows(0), columns(0) {}
    Array2(int n, int m) : rows(n), columns(m), data(n * m) {}

    int VertexIndex(int i, int j) const;
    Vector VertexValue(int i, int j) const;
    void SetVertexIndex(int i, int j, Vector v) ;
};

inline int Array2::VertexIndex(int i, int j) const
{
  return i + rows * j;
}

inline Vector Array2::VertexValue(int i, int j) const
{
  return data[i + rows * j];
}

inline void Array2::SetVertexIndex(int i, int j, Vector v) {
  data[i + rows * j] = v;
}



class Bezier_class {
  protected: 
  std::vector<Vector> n;
  std::vector<Vector> m;
  Array2 grid;

  public:
  Bezier_class(std::vector<Vector> ligne, std::vector<Vector> colonne) : n(ligne), m(colonne) , grid(static_cast<int>(ligne.size()), static_cast<int>(colonne.size())) {
    for (int i = 0; i <static_cast<int>(ligne.size()); i++) {
      for (int j = 0; j <static_cast<int>(colonne.size()); j++) {
        Vector point = operator+(n[i],m[j]);
        grid.SetVertexIndex(i,j, point);
      }
    }
  }

  Vector Vertex(float u, float v) const {
    Vector result;
    // int new_u = u * static_cast<int>(n.size());
    // int new_v = v * static_cast<int>(m.size());
    // for (int k=new_u - 3 ; k<new_u + 4; k++) {
    //   for (int l=new_v - 3; l < new_v + 4; l++) {
    for (int k=0; k<static_cast<int>(n.size()); k++) {
      for (int l=0; l<static_cast<int>(m.size()); l++) {
        float basisU = Math::Binom(static_cast<int>(n.size()) - 1 , k) * std::pow(1 - u, static_cast<int>(n.size()) - 1 - k) * std::pow(u, k);
        float basisV = Math::Binom(static_cast<int>(m.size()) - 1 , l) * std::pow(1 - v, static_cast<int>(m.size()) - 1 - l) * std::pow(v, l);
        float base = basisU * basisV;
        result.operator+=(operator*(grid.VertexValue(k,l),base));
        // std::cout << "valeur du point de controle vertex : " << result << std::endl;
      }
    }
  return result;
  }

  Vector Normal(float u, float v) const {
    Vector result_u;
    Vector result_v;
    // int new_u = u * static_cast<int>(n.size());
    // int new_v = v * static_cast<int>(m.size());
    // for (int k=new_u - 3 ; k<new_u + 4; k++) {
    //   for (int l=new_v - 3; l < new_v + 4; l++) {
     for (int k=0; k<static_cast<int>(n.size()); k++) {
      for (int l=0; l<static_cast<int>(m.size())-1; l++) {
        float basisU = Math::Binom(static_cast<int>(n.size()) -1, k) * std::pow(1 - u, static_cast<int>(n.size()) -1 - k) * std::pow(u, k);
        float basisV = Math::Binom(static_cast<int>(m.size()) -2, l) * std::pow(1 - v, static_cast<int>(m.size()) -2 - l) * std::pow(v, l);
        float dp_dv = m.size()-1 * basisU * basisV;
        result_v.operator+=(operator*(operator-(grid.VertexValue(k,l+1),grid.VertexValue(k,l)),dp_dv));
      }
    }
    // for (int k=new_u - 3 ; k<new_u + 4; k++) {
    //   for (int l=new_v - 3; l < new_v + 4; l++) {
     for (int k=0; k<static_cast<int>(n.size())-1; k++) {
      for (int l=0; l<static_cast<int>(m.size()); l++) {
        float basisU = Math::Binom(static_cast<int>(n.size()) -2, k) * std::pow(1 - u, static_cast<int>(n.size()) -2 - k) * std::pow(u, k);
        float basisV = Math::Binom(static_cast<int>(m.size()) -1, l) * std::pow(1 - v, static_cast<int>(m.size()) -1 - l) * std::pow(v, l);
        float dp_du = n.size()-1 * basisU * basisV;
        result_u.operator+=(operator*(operator-(grid.VertexValue(k+1,l),grid.VertexValue(k,l)),dp_du));
      }
    }
  result_u.operator*=(result_v);
  return result_u;
  }

  Mesh GetMesh(int nu, int nv) const;
};

 
/*!
\brief Create the mesh of the patch.
\param nu,nv Subdivisons.
*/
Mesh Bezier_class::GetMesh(int nu, int nv) const
{
  std::vector<Vector> p;
  std::vector<Vector> nn;
  std::vector<int> t;
 
  p.reserve(nu * nv);
  nn.reserve(nu * nv);
  t.reserve(nu * nv * 6);
  for (int j = 0; j < nv; j++)
  {
    float v = Math::Unit(j, nv);
    for (int i = 0; i < nu; i++)
    {
      float u = Math::Unit(i, nu);
      p.push_back(Vertex(u, v));
      nn.push_back(Normal(u, v));
    }
  }
 
  // Array2 a(Box2::Null, nu, nv);
  Array2 a( nu, nv);
  for (int i = 0; i < nu - 1; i++)
  {
    for (int j = 0; j < nv - 1; j++)
    {
      t.push_back(a.VertexIndex(i, j));
      t.push_back(a.VertexIndex(i + 1, j));
      t.push_back(a.VertexIndex(i + 1, j + 1));
      t.push_back(a.VertexIndex(i, j));
      t.push_back(a.VertexIndex(i + 1, j + 1));
      t.push_back(a.VertexIndex(i, j + 1));
    }
  }
 
  return Mesh(p, nn, t, t);
}

class Bezier_Rev {
  protected: 
  std::vector<Vector> curve;
  Vector a;
  Vector b;
  Vector x;
  Vector y;
  Vector help;
  std::vector<float> rayon;

  public:
  Bezier_Rev(std::vector<Vector> c, Vector axis_start, Vector axis_end, char ax) {
    curve = c;
    a = axis_start;
    b = axis_end;
    if (ax == 'x'){
      x = Vector(0,1,0);
      y = Vector(0,0,1);
      help = Vector(1,0,0);
      for (int i=0; i < static_cast<int>(curve.size()); i++) {
        rayon.push_back(sqrt(std::pow(curve[i][1], 2) + std::pow(curve[i][2], 2)));
      }
    }
    else if (ax == 'y'){
      x = Vector(1,0,0);
      y = Vector(0,0,1);
      help = Vector(0,1,0);
      for (int i=0; i < static_cast<int>(curve.size()); i++) {
        rayon.push_back(sqrt(std::pow(curve[i][0], 2) + std::pow(curve[i][2], 2)));
      }
    }
    else{
      x = Vector(1,0,0);
      y = Vector(0,1,0);
      help = Vector(0,0,1);
      for (int i=0; i < static_cast<int>(curve.size()); i++) {
        rayon.push_back(sqrt(std::pow(curve[i][0], 2) + std::pow(curve[i][1], 2)));
      }
    }
  }

  Vector findQ(float i) const {
    Vector result = help;
    // result = operator*(u,b);
    // result.operator+=(operator*(1-u,a));
    result.operator*=(curve[i]);
    return result;
  }

    Vector findP(Vector q, float phi, float r) const {
    Vector result = q;
    result.operator+=(operator+(operator*(r*cos(phi),x),operator*(r*sin(phi),y)));
    return result;
  }

    Vector Normals(float phi) const {
    Vector result;
    result = operator+(operator*(-sin(phi),x),operator*(cos(phi),y));
    return result;
  }


  Mesh GetMesh(int p) const;
};


Mesh Bezier_Rev::GetMesh(int p) const
{
  double pi = 3.14159265358979323846;
  std::vector<Vector> pp;
  std::vector<Vector> nn;
  std::vector<int> t;
 
  pp.reserve(static_cast<int>(curve.size()) * p);
  nn.reserve(static_cast<int>(curve.size()) * p);
  t.reserve(static_cast<int>(curve.size()) * p * 6);

  for (int i=0; i < static_cast<int>(curve.size()); i++) {
    // float u = Math::Unit(i,p);
    Vector qt = findQ(i);
    for (int j=0; j < p; j++) { 
      float phi = 2 * j * pi / (p-1);
      pp.push_back(findP(qt,phi, rayon[i]));
      nn.push_back(Normals(phi));
    }
  }

  for (int i = 0; i < static_cast<int>(curve.size()) ; i++) {
    for (int j = 0; j < p - 1; j++) {
        int currentIndex = i * p + j;
        int nextIndex = i * p + (j + 1);
        int nextRowIndex = ((i + 1) % static_cast<int>(curve.size())) * p + (j + 1);
        int rowIndex = ((i + 1) % static_cast<int>(curve.size())) * p + j;

        // Premier triangle
        t.push_back(currentIndex);
        t.push_back(nextIndex);
        t.push_back(rowIndex);

        // Deuxième triangle
        t.push_back(nextIndex);
        t.push_back(nextRowIndex);
        t.push_back(rowIndex);
    }
  }

  return Mesh(pp, nn, t, t);
}
