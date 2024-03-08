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
  float taille_X;
  float taille_Y;
  float Temps;
  float pas;
  float resolution;

  Grille(int X, int Y, int Time, float res, float p);
  Grille(){};
  bi_vecteur<int> localisation(const float &x, const float &y) const;
  int find(const float &x, const float &y,const float &t)const{
    // Takes position and time (in unit) and outputs the coordinate in the vector
    return int(x) + int(y)*int(taille_X/pas+1) + int(t)*int(taille_Y/pas + taille_X/pas);
  };
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