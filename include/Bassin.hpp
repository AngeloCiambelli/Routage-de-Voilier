#ifndef DEF_BASSIN_HPP
#define DEF_BASSIN_HPP

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
#include "Foncteur.hpp"
#include "Grille.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe Bassin pour stocker les champs de vents et de courants de facon soit
// analytique (fonction de la grille) ou de facon tabulée (en tableau)
//
// Note: 
//
//===========================================================================
//                 Definition de la classe Bassin
//===========================================================================

class Bassin
{
public:
  pair<float, float>      coin_bas_gauche;
  pair<float, float>      coin_haut_droit;
  Grille                  grille;
  bi_vecteur<float>       champs_vent;
  bi_vecteur<float>       champs_courant;
  foncteur_vent           fonction_vent;
  foncteur_courant        fonction_courant;
  string                  stockage;

  Bassin(const pair<float, float> &a, const pair<float, float> &b, const float &pas, foncteur_vent &f_vent, foncteur_courant &f_courant, const string &s)
  {
    coin_bas_gauche = a;
    coin_haut_droit = b;
    stockage = s;
    fonction_vent = f_vent;
    fonction_courant = f_courant;

    grille = Grille(abs(b.first - a.first), abs(b.second - a.second), 1, 1, pas);
    champs_vent = bi_vecteur<float>();
    champs_courant = bi_vecteur<float>();

    if (s == "tabule")
    {
      champs_vent = bi_vecteur<float>();
      champs_courant = bi_vecteur<float>();  
      
      for (int i = 0; i < grille.taille_Y/grille.pas; i++)
      {
        for (int j = 0; j < grille.taille_X/grille.pas; j++)
        {
          champs_vent.pushback(f_vent(float(j)*pas, float(i)*pas));
          //cout << "champs vent" << champs_vent;
          champs_courant.pushback(f_courant(float(j)*pas, float(i)*pas));
          //cout << "champs courant" << champs_courant;
        }
      }
    }
  };

  Bassin() : champs_vent(), champs_courant()
  {
    coin_bas_gauche = pair(0, 0);
    coin_haut_droit = pair(0, 0);
  };
};

#endif