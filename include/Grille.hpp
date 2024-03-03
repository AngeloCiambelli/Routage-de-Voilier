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
#include "Bi_vecteur.hpp"

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


class Grille
{
public:
  int taille_X;
  int taille_Y;
  int Temps;
  float pas;
  float resolution;

  Grille(int X, int Y, int Time, float res, float p);
  Grille(){};
  bi_vecteur<int> localisation(const float &x, const float &y) const;
  int find(const float &x, const float &y,const float &t)const{
    return x + y*taille_X + t*(taille_Y + taille_X);
  }
};

Grille::Grille(int X, int Y, int Time, float res, float p)
{
  taille_X = X;
  taille_Y = Y;
  Temps = Time;
  resolution = res;
  pas = p;
};

bi_vecteur<int> Grille::localisation(const float &x, const float &y) const {
    // rend les quatres indices des points ABCD correspondant au rectangle ABCD
    // dans lequel se trouve le point de coordonnée (x,y) (A en bas gauche, D au-dessus de A)
    vecteur<int> Xs(4);
    vecteur<int> Ys(4);
    Xs[0] = int(floor(x/pas));
    Ys[0] = int(floor(y/pas));
    Xs[1] = Xs[0] + 1;
    Ys[1] = Ys[0];
    Xs[2] = Xs[1];
    Ys[2] = Ys[1] + 1;
    Xs[3] = Xs[0];
    Ys[3] = Ys[2];
    bi_vecteur<int> result(Xs,Ys);
    return result;
}

#endif