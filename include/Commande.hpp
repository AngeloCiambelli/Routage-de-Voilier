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
#include "Foncteur.hpp"


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

class Commande
{
public:
  foncteur_commande commande_f;
  vecteur<float> vecteur_commande;
  string stockage;

  Commande(const foncteur_commande &f)
  {
    stockage = "analytique";
    commande_f = f;
  }
  Commande(const vecteur<float> &v)
  {
    stockage = "tabule";
    vecteur_commande = v;
  }
  Commande(){}
};

#endif