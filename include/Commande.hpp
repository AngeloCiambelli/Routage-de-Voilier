#ifndef DEF_COMMANDE_HPP
#define DEF_COMMANDE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"


using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe contenant le vecteur des commandes.
//
// Note: Pas de fichier cpp a cause des templates
//
//===========================================================================
//                            Definition de la classe
//===========================================================================

template <typename T1, typename T2>
class commande
{
public:
  vecteur<T2> vecteur_commande;
  string nom_fonction;

  commande(string fonction, vecteur<T1> delta_t)
  {
    nom_fonction = fonction;
    if (fonction == "cos")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        vecteur_commande.push_back(cos(delta_t[i]));
      };
    }
    if (fonction == "sin")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        vecteur_commande.push_back(sin(delta_t[i]));
      };
    }
    if (fonction == "constant")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        int c = 3;
        vecteur_commande.push_back(c * delta_t[i]);
      };
    }
    if (fonction == "")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        vecteur_commande.push_back(0 * delta_t[i]);
      };
    }
  }
};

#endif