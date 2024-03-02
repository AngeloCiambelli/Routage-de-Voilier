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

class bassin
{
public:
  pair<float, float>      coin_bas_gauche;
  pair<float, float>      coin_haut_droit;
  Grille<vecteur<float>>  champs_vent;
  Grille<vecteur<float>>  champs_courant;
  foncteur_vent           fonction_vent;
  foncteur_courant        fonction_courant;
  string                  stockage;

  bassin(const pair<float, float> &a, const pair<float, float> &b, const float &pas, foncteur_vent &f_vent, foncteur_courant &f_courant, const string &s)
  {
    coin_bas_gauche = a;
    coin_haut_droit = b;
    stockage = s;

    if (s == "analytique")
    {
      fonction_vent = f_vent;
      fonction_courant = f_courant;

      champs_vent = Grille<vecteur<float>>(abs(a.first - b.first), abs(b.second - a.second), 1, 1, pas);
      champs_courant =  Grille<vecteur<float>>(abs(a.first - b.first), abs(b.second - a.second), 1, 1, pas);
    }

    else if (s == "tableau")
    {
      champs_vent = Grille<vecteur<float>>(abs(a.first - b.first), abs(b.second - a.second), 1, 1, pas);
      champs_courant =  Grille<vecteur<float>>(abs(a.first - b.first), abs(b.second - a.second), 1, 1, pas);

      //  A coder avec des append et utiliser le constructeur vide en haut
      for (int i = 0; i < (champs_vent.valeur[0]).size(); i++)
      {
        for (int j = 0; j < (champs_vent.valeur[0][i]).size(); j++)
        {
          champs_vent.valeur[0][i][j] = f_vent(i * pas, j * pas);
          champs_courant.valeur[0][i][j] = f_courant(i * pas, j * pas);
        }
      }
    }
  };

  bassin() : champs_vent(), champs_courant()
  {
    coin_bas_gauche = pair(0, 0);
    coin_haut_droit = pair(0, 0);
  };
};

#endif