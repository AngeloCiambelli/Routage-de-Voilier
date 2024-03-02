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
T1 interpolation(bi_vecteur<int> position, const int &timestamp, T2 valeur, Grille grille){
  T1 sum = T1();
  int x1 = position.X[0];int x2 = position.X[2];
  int y1 = position.Y[0];int y2 = position.Y[2];
  float D = (x2-x1)*(y2-y1);
  w11 = (x2 - x)*(y2 - y)/D;
  w12 = (x2 - x)*(y - y1)/D;
  w21 = (x - x1)*(y2 - y)/D;
  w22 = (x - x1)*(y - y1)/D;
  sum = valeur[grille.find(x1,y1,timestamp)]*w11 + valeur[grille.find(x1,y2,timestamp)]*w21 + valeur[grille.find(x2,y1,timestamp)]*w12 + valeur[grille.find(x2,y2,timestamp)]*w22;
  return sum;
};

#endif