#ifndef DEF_GRILLE_HPP
#define DEF_GRILLE_HPP

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
// Classe Grille décrivant la grille de discretisation spatiale et localisation 
// d'un rectangle contenant un point.
//
// Note: Pas de fichier cpp a cause du template
//
//===========================================================================
//                            Definition de la classe Grille
//===========================================================================

template <typename T>
class Grille
{
public:
  int taille_X;
  int taille_Y;
  int Temps;
  float pas;
  float resolution;
  vecteur<vecteur<vecteur<T>>> valeur;

  Grille(int X, int Y, int Time, float res, float p);
  Grille(){};
  bi_vecteur<int> localisation(const float &x, const float &y);
  float operator()(int t, int j, int i)
  {
    if (i >= taille_X || j >= taille_Y)
    {
      cout << "Erreur : indices non-valides";
      exit(1);
    }
    return valeur[t][j][i];
  };
  T interpolation(const float &x, const float &y, const int &timestamp);
  pair<vecteur<vecteur<float>>, vecteur<vecteur<float>>> separation()
  {
    vecteur<vecteur<float>> X(this->taille_Y/this->pas, vecteur<float>(this->taille_X/this->pas));
    vecteur<vecteur<float>> Y(this->taille_Y/this->pas, vecteur<float>(this->taille_X/this->pas));

    for (int i = 0; i < this->taille_Y/this->pas; i++)
    {
      for (int j = 0; j <this->taille_X/this->pas; j++)
      {
        X[i][j] = (*this).valeur[0][i][j][0];
        Y[i][j] = (*this).valeur[0][i][j][1];
      }
    }
    return(pair(X,Y));
  };
};

template <typename T>
Grille<T>::Grille(int X, int Y, int Time, float res, float p)
{
  vecteur<vecteur<vecteur<T>>> tmp(
      Time / res,
      vecteur<vecteur<T>>(
          Y / p,
          vecteur<T>(X / p)));
  taille_X = X;
  taille_Y = Y;
  Temps = Time;
  resolution = res;
  pas = p;
  valeur = tmp;
};

// template<typename T>
// bi_vecteur<int> Grille<T>::localisation(const float &x, const float &y){
//     // rend les quatres indices des points ABCD correspondant au rectangle ABCD
//     // dans lequel se trouve le point de coordonnée (x,y) (A en bas gauche, D au-dessus de A)
//     vecteur<int> Xs(4);
//     vecteur<int> Ys(4);
//     Xs[0] = int(floor(x/resolution));
//     Ys[0] = int(floor(y/resolution));
//     Xs[1] = Xs[0] + 1;
//     Ys[1] = Ys[0];
//     Xs[2] = Xs[1];
//     Ys[2] = Ys[1] + 1;
//     Xs[3] = Xs[0];
//     Ys[3] = Ys[2];
//     bi_vecteur<int> result(Xs,Ys);
//     return result;
// }

// template<typename T>
// T Grille<T>::interpolation(const float &x, const float &y, const int &timestamp){
//   T sum = T();
//   bi_vecteur position = localisation(const float &x, const float &y);
//   float w11;float w12;float w21; float w22;
//   float x1;float x2;float y1; float y2;
//   x1 = position.X[0];x2 = position.X[2];
//   y1 = position.Y[0];y2 = position.Y[2];
//   float D = (x2-x1)(y2-y1);
//   w11 = (x2 - x)(y2 - y)/D;
//   w12 = (x2 - x)(y - y1)/D;
//   w21 = (x - x1)(y2 - y)/D;
//   w22 = (x - x1)(y - y1)/D;
//   sum = valeur[timestamp][y1][x1]*w11 + valeur[timestamp][y2][x1]*w21 + valeur[timestamp][y1][x2]*w12 + valeur[timestamp][y2][x2]*w22;
//   return sum;
// };

#endif