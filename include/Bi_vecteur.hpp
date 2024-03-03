#ifndef DEF_BI_VECTEUR_HPP
#define DEF_BI_VECTEUR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe capable de gérer les champs de courants et vents et listes de points.
//
// Note: Pas de fichier cpp a cause du template
//
//===========================================================================
//                            Definition de la classe
//===========================================================================

template <typename T>
class bi_vecteur
{
public:
  vecteur<T> X;
  vecteur<T> Y;
  bi_vecteur(const vecteur<T> &_X, const vecteur<T> &_Y)
  {
    X = _X;
    Y = _Y;
  };
  bi_vecteur()
  {
    X = {};
    Y = {};
  };

  vecteur<T> operator[](const int &i) const {return vecteur{(*this).X[i], (*this).Y[i]};};
  bi_vecteur<T> &operator=(const bi_vecteur<T> &vect)
  {
    this->X = vect.X;
    this->Y = vect.Y;
    return *this;
  };
  bi_vecteur<T> &pushback(pair<T, T> xy)
  {
    (this->X).push_back(xy.first);
    (this->Y).push_back(xy.second);
    return *this;
  }
  int size(){return X.size()}
};

//===========================================================================
//                            Fonctions externes
//===========================================================================

template <typename T>
ostream &operator<<(ostream &out, const bi_vecteur<T> &v)
{
  out << "[" << v.X << "," << v.Y << "]";
  return (out);
};

#endif