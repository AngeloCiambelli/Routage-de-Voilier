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
// Note: Pas de fichier cpp a cause du template. 
// X et Y ne sont pas en privé pour pouvoir y accéder facilement.
//
//===========================================================================
//                            Definition de la classe
//===========================================================================

template <typename T>
class Bi_vecteur
{
  public:
    Vecteur<T> X;
    Vecteur<T> Y;

    Bi_vecteur(const Vecteur<T> &_X, const Vecteur<T> &_Y);
    Bi_vecteur();

    Vecteur<T> operator[](const int &i) const;
    Bi_vecteur<T> &operator=(const Bi_vecteur<T> &vect);
    Bi_vecteur<T> &pushback(Vecteur<T> xy);
    int size();
};

//===========================================================================
//                            Fonctions membres
//===========================================================================

template<typename T>
Bi_vecteur<T>::Bi_vecteur(const Vecteur<T> &_X, const Vecteur<T> &_Y)
{
  X = _X;
  Y = _Y;
};

template<typename T>
Bi_vecteur<T>::Bi_vecteur()
{
  X = {};
  Y = {};
};

template<typename T>
Vecteur<T> Bi_vecteur<T>::operator[](const int &i) const 
{
  return Vecteur{(*this).X[i], (*this).Y[i]};
};

template<typename T>
Bi_vecteur<T>& Bi_vecteur<T>::operator=(const Bi_vecteur<T> &vect)
{
  this->X = vect.X;
  this->Y = vect.Y;
  return *this;
};

template<typename T>
Bi_vecteur<T>& Bi_vecteur<T>::pushback(Vecteur<T> xy)
{
  (this->X).push_back(xy[0]);
  (this->Y).push_back(xy[1]);
  return *this;
};

template<typename T>
int Bi_vecteur<T>::size()
{
  return X.size();
};

//===========================================================================
//                            Fonctions externes
//===========================================================================

template <typename T>
ostream &operator<<(ostream &out, const Bi_vecteur<T> &v)
{
  out << "[" << v.X << "," << v.Y << "]";
  return (out);
};

#endif