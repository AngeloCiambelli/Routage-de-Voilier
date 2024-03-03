#ifndef DEF_FONCTION_EXTERNE_HPP
#define DEF_FONCTION_EXTERNE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"
#include "Grille.hpp"
#include "Bi_vecteur.hpp"

using namespace std;


template<typename T1, typename T2>  
// T1 : float, int , ou vect<float> X,Y
// T2 : vect ou bivect <float>
T1 interpolation(const bi_vecteur<int> position, const int &timestamp, const T2 valeur, const Grille grille){
  T1 sum = T1();
  int x1 = position.X[0];int x2 = position.X[2];
  int y1 = position.Y[0];int y2 = position.Y[2];
  float D = (x2-x1)*(y2-y1);
  int w11 = (x2 - x)*(y2 - y)/D;
  int w12 = (x2 - x)*(y - y1)/D;
  int w21 = (x - x1)*(y2 - y)/D;
  int w22 = (x - x1)*(y - y1)/D;
  sum = valeur[grille.find(x1,y1,timestamp)]*w11 + valeur[grille.find(x1,y2,timestamp)]*w21 + valeur[grille.find(x2,y1,timestamp)]*w12 + valeur[grille.find(x2,y2,timestamp)]*w22;
  return sum;
};




template<typename T>
vecteur<pair<vecteur<vecteur<T>>, vecteur<vecteur<T>>>> bi_vecteur_vers_table(const bi_vecteur<T>& v,const Grille& grille)
{
  vecteur<pair<vecteur<vecteur<T>>, vecteur<vecteur<T>>>> table(grille.Temps/grille.resolution, 
                                  pair(vecteur<vecteur<T>>(grille.taille_Y/grille.pas, vecteur<T>(grille.taille_X/grille.pas)), 
                                       vecteur<vecteur<T>>(grille.taille_Y/grille.pas, vecteur<T>(grille.taille_X/grille.pas))));

  for (int t=0; t<grille.Temps/grille.resolution; t++)
  {
    for (int i=0; i<grille.taille_Y/grille.pas; i++)
    {
      for (int j=0; j<grille.taille_Y/grille.pas; j++)
      {
        ((table[t]).first)[i][j] = v[j + i*grille.taille_X + t*(grille.taille_Y + grille.taille_X)][0];
        ((table[t]).second)[i][j] = v[j + i*grille.taille_X + t*(grille.taille_Y + grille.taille_X)][1];
      }
    }
  }
  return table;
};

#endif