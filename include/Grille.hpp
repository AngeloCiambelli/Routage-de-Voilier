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

  Grille(float X, float Y, float Time, float res, float p);
  Grille(){};


  Bi_vecteur<int> localisation(const float &x, const float &y) const;
 

  int find(const int &x, const int &y,const int &t)const{
    // Prends la position et le temps en entier, et retourne la position dans le vecteur de valeur associée à la grille
    return x + y*(int(taille_X/pas)+1) + t*(int(taille_Y/pas)+1)*(int(taille_X/pas)+1);
  };

};

Grille::Grille(float X, float Y, float Time, float res, float p)
{  // constructeur par défaut
  taille_X = X;
  taille_Y = Y;
  Temps = Time;
  resolution = res;
  pas = p;
};

Bi_vecteur<int> Grille::localisation(const float &x, const float &y) const {
    // rend les quatres indices des points ABCD correspondant au rectangle ABCD
    // dans lequel se trouve le point de coordonnée (x,y) (A en bas gauche, D au-dessus de A)
    Vecteur<int> Xs(4);
    Vecteur<int> Ys(4);

    Xs[0] = int(floor(x/pas));
    Ys[0] = int(floor(y/pas));
    Xs[1] = Xs[0] + 1;
    Ys[1] = Ys[0];
    Xs[2] = Xs[1];
    Ys[2] = Ys[1] + 1;
    Xs[3] = Xs[0];
    Ys[3] = Ys[2];

    Bi_vecteur<int> result(Xs,Ys);
    return result;
}

#endif