#ifndef DEF_COMMANDE_DISCRETE_HPP
#define DEF_COMMANDE_DISCRETE_HPP

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
// Classe commande discrete fournissant la liste des valeurs discrètes des commandes 
// et une description de contraintes simples.
//
// Note: Pas de fichier cpp a cause des templates
//
//===========================================================================
//                 Definition de la class Commande_discrete
//===========================================================================

class commandes_discretes
{
public:
  vecteur<float> commandes;
  float contrainte;
  bool check_commandes()
  {
    float a = commandes[0];
    for (int i = 1; i < commandes.size(); i++)
    {
      if (fmod(abs(commandes[i] - a), 360.) > contrainte)
      {
        cout << "Erreur : commande invalide. Il y a un changment brusque de direction.";
      }
      a = commandes[i];
    }
  }
};

#endif