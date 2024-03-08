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
#include "Bassin.hpp"

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template<typename T1, typename T2>  
// T1 : float, int , ou vect<float> X,Y
// T2 : vect ou bivect <float>
T1 interpolation(const bi_vecteur<int> &position_rect, const float &x, const float &y, const int &timestamp, const T2 &valeur,const Grille& grille){
  T1 sum;
  float x1 = float(position_rect.X[0])*grille.pas;float x2 = float(position_rect.X[2])*grille.pas;
  float y1 = float(position_rect.Y[0])*grille.pas;float y2 = float(position_rect.Y[2])*grille.pas;
  float D = (x2-x1)*(y2-y1);
  float w11 = abs((x2 - x)*(y2 - y)/D);
  float w12 = abs((x2 - x)*(y - y1)/D);
  float w21 = abs((x - x1)*(y2 - y)/D);
  float w22 = abs((x - x1)*(y - y1)/D);
  cout << "bas_gauche" << valeur[grille.find(position_rect.X[0],position_rect.Y[0],timestamp)] 
       << "haut_gauche" << valeur[grille.find(position_rect.X[0],position_rect.Y[2],timestamp)] 
       << "bas_droit" << valeur[grille.find(position_rect.X[2],position_rect.Y[0],timestamp)] 
       << "haut_droit" << valeur[grille.find(position_rect.X[2],position_rect.Y[2],timestamp)] << endl;

  sum = valeur[grille.find(position_rect.X[0],position_rect.Y[0],timestamp)]*w11 + 
        valeur[grille.find(position_rect.X[0],position_rect.Y[2],timestamp)]*w12 + 
        valeur[grille.find(position_rect.X[2],position_rect.Y[0],timestamp)]*w21 + 
        valeur[grille.find(position_rect.X[2],position_rect.Y[2],timestamp)]*w22;
  return sum;
};


float interpolation(const bi_vecteur<int>& indice_rect, const bi_vecteur<int>& entete, const float &x, const float &y, const vecteur<vecteur<float>>& valeur){
  float sum = float();
  float i1 = indice_rect.X[2];float i2 = indice_rect.X[1];
  float j1 = indice_rect.Y[2];float j2 = indice_rect.Y[1];

  float x1 = entete.X[i1];float x2 = entete.X[i2];
  float y1 = entete.Y[j1];float y2 = entete.Y[j2];

  float D = (x2-x1)*(y2-y1);
  float w11 = abs((x2 - x)*(y2 - y)/D);
  float w12 = abs((x2 - x)*(y - y1)/D);
  float w21 = abs((x - x1)*(y2 - y)/D);
  float w22 = abs((x - x1)*(y - y1)/D);
  sum = valeur[i1][j1]*w11 + valeur[i1][j2]*w12 + valeur[i2][j1]*w21 + valeur[i2][j2]*w22;
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

bool controle_position(const vecteur<float> &position, const Bassin &bassin)
{ 
  cout << bassin.coin_bas_gauche.second << bassin.coin_haut_droit.second;
  bool test     ((bassin.coin_bas_gauche.first <= position[0]) 
            and (position[0] <= bassin.coin_haut_droit.first) 
            and (bassin.coin_bas_gauche.second <= position[1]) 
            and (position[1] <= bassin.coin_haut_droit.second));
  return test;
};

float angle(vecteur<float> v)
{
  float valeur;
  if (v[0] < 0){valeur = float(180) - (acos(-v[0]/sqrt(v|v))*float(180)/(atan(float(1))*float(4)));}
  else {valeur = acos(-v[0]/sqrt(v|v))*float(180)/(atan(float(1))*float(4));}
  return sgn(v[1])*valeur;
}

vecteur<float> create_v0(Grille grille){
  int n = int(grille.taille_X/grille.pas);
  int m = int(grille.taille_Y/grille.pas);
  vecteur<float> v0(n*m);
  for(int j=0; j<m; j++){
    for(int i=0;i<n; i++){
      float floati = float(i);float floatj = float(j);float floatn = float(n);float floatm = float(m);
      v0[i+n*j] = float(pow(floati-2./3.*floatn, 2.) + pow(floatj-2./3.*floatm, 2.) - 1.);
    }
  }
  return v0;
};



#endif