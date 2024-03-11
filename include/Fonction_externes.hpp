#ifndef DEF_FONCTION_EXTERNES_HPP
#define DEF_FONCTION_EXTERNES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Vecteur.hpp"
#include "Grille.hpp"
#include "Bi_vecteur.hpp"
#include "Bassin.hpp"


using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Fonctions externes au classes qui sont utilisés dans le code
//
//===========================================================================
//                            Implémentation
//===========================================================================

// Fonction qui trouve le signe d'un float
template <typename T> 
int sgn(T val) 
{
    return (T(0) < val) - (val < T(0));
}

template<typename T1, typename T2>  
// T1 : float, int , ou vect<float> X,Y
// T2 : vect ou bivect <float>
T1 interpolation(const Bi_vecteur<int> &position_rect, const float &x, const float &y, const int &timestamp, const T2 &valeur,const Grille& grille){
  // interpole la valeur en x et y depuis le vecteur valeur associé à grille, connaissant les quatres points formant le rectangle 
  // dans lequel le point (x,y) est inscrit
  T1 sum;
  float x1 = float(position_rect.X[0])*grille.pas;float x2 = float(position_rect.X[2])*grille.pas; // mets les quatres points du rectangle 
  float y1 = float(position_rect.Y[0])*grille.pas;float y2 = float(position_rect.Y[2])*grille.pas; // dans la bonne unité pour les calculs


  if (x1<0 || y1<0 || x2>grille.taille_X/grille.pas || y2>grille.taille_Y/grille.pas){ 
    // si on se trouve en dehors de la zone d'étude, on émet une exception
    throw std::invalid_argument("interpolation en dehors de la zone définie impossible");
  }

  // Calcul des poids d'interpolation
  float D = (x2-x1)*(y2-y1);
  float w11 = abs((x2 - x)*(y2 - y)/D);
  float w12 = abs((x2 - x)*(y - y1)/D);
  float w21 = abs((x - x1)*(y2 - y)/D);
  float w22 = abs((x - x1)*(y - y1)/D);

  // Calcul de l'interpolation
  sum = valeur[grille.find(position_rect.X[0],position_rect.Y[0],timestamp)]*w11 + 
        valeur[grille.find(position_rect.X[0],position_rect.Y[2],timestamp)]*w12 + 
        valeur[grille.find(position_rect.X[2],position_rect.Y[0],timestamp)]*w21 + 
        valeur[grille.find(position_rect.X[2],position_rect.Y[2],timestamp)]*w22;
  return sum;
};

//Fonction d'interpolation des polaires. Elle fonctionne similairement à l'interpolation précédente.
float interpolation(const Bi_vecteur<int>& indice_rect, const Bi_vecteur<float>& entete, const float &x, const float &y, const Vecteur<Vecteur<float>>& valeur){
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

// Fonction qui convertit un Bi_vecteur<T> de stockage d'une grille en tables des X et tables des Y pour chaque pas de temps
template<typename T>
Vecteur<pair<Vecteur<Vecteur<T>>, Vecteur<Vecteur<T>>>> bi_vecteur_vers_table(const Bi_vecteur<T>& v,const Grille& grille)
{
  // Définition de l'objet final contenant les pair de tables X et Y
  Vecteur<pair<Vecteur<Vecteur<T>>, Vecteur<Vecteur<T>>>> table(grille.Temps/grille.resolution, 
                                  pair(Vecteur<Vecteur<T>>(grille.taille_Y/grille.pas+1, Vecteur<T>(grille.taille_X/grille.pas+1)), 
                                       Vecteur<Vecteur<T>>(grille.taille_Y/grille.pas+1, Vecteur<T>(grille.taille_X/grille.pas+1))));

  // Remplissage
  for (int t=0; t<(grille.Temps/grille.resolution); t++)
  {
    for (int i=0; i<=grille.taille_Y/grille.pas; i++)
    {
      for (int j=0; j<=grille.taille_X/grille.pas; j++)
      {
        ((table[t]).first)[i][j] = v[j + i*(grille.taille_X/grille.pas+1) + t*(grille.taille_Y + grille.taille_X)/grille.pas][1];
        ((table[t]).second)[i][j] = v[j + i*(grille.taille_Y/grille.pas+1) + t*(grille.taille_Y + grille.taille_X)/grille.pas][0];
      }
    }
  }
  return table;
};

// Fonction qui vérifie si la position (x,y) est toujours dans le bassin
bool controle_position(const Vecteur<float> &position, const Bassin &bassin)
{ 
  bool test     ((bassin.coin_bas_gauche.first <= position[0]) 
            and (position[0] <= bassin.coin_haut_droit.first) 
            and (bassin.coin_bas_gauche.second <= position[1]) 
            and (position[1] <= bassin.coin_haut_droit.second));
  return test;
};

// Fonction qui donne l'angle absolu d'un vecteur (de 180° à -180°)
float angle(Vecteur<float> v)
{
  // Definition de la variable
  float valeur;

  if (v[0] < 0)
  {
    valeur = float(180) - (acos(-v[0]/sqrt(v|v))*float(180)/(atan(float(1))*float(4)));
  }
  else 
  {
    valeur = acos(v[0]/sqrt(v|v))*float(180)/(atan(float(1))*float(4));
  }
  return (sgn(v[1])*valeur);
}

Vecteur<float> create_v0(const Grille &grille){
  // création analytique d'un vecteur des scores, associé à la grille en entrée
  float b = 40.; // Scaling pour la taille de la zone cible
  float c = grille.taille_X;  // Constante pour que taille de la zone cible soit cohérente avec la taille de la zone globale
  int n = int(grille.taille_X/grille.pas);
  int m = int(grille.taille_Y/grille.pas);

  Vecteur<float> v0((n+1)*(m+1));
  for(int j=0; j<=m; j++){
    for(int i=0;i<=n; i++){
      float floati = float(i)*grille.pas;float floatj = float(j)*grille.pas; // on met les points à la bonne unité
      float floatn = float(n)*grille.pas;float floatm = float(m)*grille.pas;
      v0[i+(n+1)*j] = float(b/(c*c)*pow(floati-2./3.*c,2.) + b/(c*c)*pow(floatj-2./3.*c,2.) - 1.); // focntion de score, crée une zone carrée
    }
  }
  return v0;
};

// Fonction qui calcule l'angle relatif entre deux angles absolus
float angle_relatif(float u, float v)
{
  // Definition de la variable
  float angle_relatif;

  if (sgn(u)==sgn(v))
  {
    angle_relatif = abs(abs(u)-abs(v));
  }
  else
  {
    angle_relatif = min(abs(u)+abs(v),(180 - abs(u) + 180 - abs(v)));
  }

  return(angle_relatif);
}

void print_grille(const Grille &grille,const Vecteur<float> &val){
  // fonction pour afficher les vecteurs de façon élégante, en cohérence avec la grille associée
  for(int t = 0; t<=int(grille.Temps/grille.resolution); t++){
        for(int j = 0; j<=int(grille.taille_Y/grille.pas); j++){
            for(int i = 0; i<=int(grille.taille_X/grille.pas); i++){
              float valeur = val[grille.find(i,j,t)];
              cout << setprecision(2) << fixed << setw(5) << valeur << " "; // si les valeurs ne sont pas trop grande en absolu, 
                                                            //l'affichage de la grille sera un rectangle parfait, facile à lire
              
            }
            cout << endl;
        }
        cout << endl << t+1 << endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl <<endl;
    }
}

#endif