#ifndef DEF_FONCTION_EXTERNES_HPP
#define DEF_FONCTION_EXTERNES_HPP

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
T1 interpolation(const bi_vecteur<int>& position_rect,  const float &x, const float &y, const int &timestamp, const T2& valeur,const Grille& grille){
  T1 sum = T1();
  int x1 = position_rect.X[0]*grille.pas;int x2 = position_rect.X[2]*grille.pas;
  int y1 = position_rect.Y[0]*grille.pas;int y2 = position_rect.Y[2]*grille.pas;
  float D = abs((x2-x1))*abs((y2-y1));
  float w11 = abs((x2 - x)*(y2 - y)/D);
  float w12 = abs((x2 - x)*(y - y1)/D);
  float w21 = abs((x - x1)*(y2 - y)/D);
  float w22 = abs((x - x1)*(y - y1)/D);
  cout << "w11=" <<  w11 << "w12=" <<  w12 << "w21=" << w21 << "w22=" << w22 << endl;
  sum = valeur[grille.find(x1,y1,timestamp)]*w11 + valeur[grille.find(x1,y2,timestamp)]*w21 + valeur[grille.find(x2,y1,timestamp)]*w12 + valeur[grille.find(x2,y2,timestamp)]*w22;
  return sum;
};


float interpolation(const bi_vecteur<int>& position_rect, const float &x, const float &y, const vecteur<vecteur<float>>& valeur){
  float sum = float();
  int x1 = position_rect.X[2];int x2 = position_rect.X[1];
  int y1 = position_rect.Y[2];int y2 = position_rect.Y[1];
  float D = (x2-x1)*(y2-y1);
  float w11 = abs((x2 - x)*(y2 - y)/D);
  float w12 = abs((x2 - x)*(y - y1)/D);
  float w21 = abs((x - x1)*(y2 - y)/D);
  float w22 = abs((x - x1)*(y - y1)/D);
  sum = valeur[x1][y1]*w11 + valeur[x1][y2]*w21 + valeur[x2][y1]*w12 + valeur[x2][y2]*w22;
  return sum;
};

template<typename T>
vecteur<pair<vecteur<vecteur<T>>, vecteur<vecteur<T>>>> bi_vecteur_vers_table(const bi_vecteur<T>& v,const Grille& grille)
{
  vecteur<pair<vecteur<vecteur<T>>, vecteur<vecteur<T>>>> table(grille.Temps/grille.resolution, 
                                  pair(vecteur<vecteur<T>>(grille.taille_Y/grille.pas+1, vecteur<T>(grille.taille_X/grille.pas+1)), 
                                       vecteur<vecteur<T>>(grille.taille_Y/grille.pas+1, vecteur<T>(grille.taille_X/grille.pas+1))));

  for (int t=0; t<(grille.Temps/grille.resolution); t++)
  {
    for (int i=0; i<=grille.taille_Y/grille.pas; i++)
    {
      for (int j=0; j<=grille.taille_X/grille.pas; j++)
      {
        ((table[t]).first)[i][j] = v[j + i*(grille.taille_X/grille.pas+1) + t*(grille.taille_Y + grille.taille_X)/grille.pas][0];
        ((table[t]).second)[i][j] = v[j + i*(grille.taille_Y/grille.pas+1) + t*(grille.taille_Y + grille.taille_X)/grille.pas][1];
      }
    }
  }
  return table;
};

#endif