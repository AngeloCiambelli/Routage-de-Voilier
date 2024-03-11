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
#include "Voilier.hpp"
#include "Foncteur.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe contenant les commandes, de manière analytique ou tabulée. 
// i.e l'angle absolu en *degré* que notre bateau devra prendre a chaque pas de temps.
//
// Note: 
//
//===========================================================================
//                            Definition de la classe
//===========================================================================

class Commande
{
public:
  Foncteur_commande commande_f;         // Commande en mode fonction
  Vecteur<float> vecteur_commande;      // Vecteur de commande
  string stockage;                      // Pour retenir sous quel formes sont stockés nos commandes

  // Constructeurs
  Commande(const Foncteur_commande &f); // Constructeur pour créer des commandes analytiquement (fonction de l'angle d'arrivée)
  Commande(const Vecteur<float> &v);    // Constructeur pour créer des commandes à partir d'un vecteur
  Commande(){}

  // Fonctions membres
  void verification_commande(const Voilier<float, float> &voilier); // Fonction vérifiant que les commandes respectent les contraintes du voilier
};

//===========================================================================
//                            Fonctions membres
//===========================================================================

Commande::Commande(const Foncteur_commande &f)
{
  stockage = "analytique";
  commande_f = f;
};

Commande::Commande(const Vecteur<float> &v)
{
  stockage = "tabule";
  vecteur_commande = v;
};

void Commande::verification_commande(const Voilier<float, float> &voilier)
{
  if (stockage=="tabule")
  {
    for (int i=0; i<(*this).vecteur_commande.size()-1; i++)
    {
      //Stocker temporairement ma commande i
      float ma_commande = angle_relatif((*this).vecteur_commande[i],(*this).vecteur_commande[i+1]);
      
      //verifier que les commandes ne change pas trop entre chaque pas de temps
      if (  (voilier.contrainte_commande.first >= ma_commande) or (ma_commande >= voilier.contrainte_commande.second))
      {
        cout << "Les commandes sont imcompatibles avec le voilier" << endl; exit(1); 
      }
    }
  }

  else if (stockage=="analytique")
  {
    // Angle d'arrivée test
    float angle_test = -180;

    //Pour tout angle d'arrivée, on regarde que la commande resultante respecte les contraintes
    while (angle_test <= 180)
    {
      //Stocker temporairement ma commande
      float ma_commande = angle_relatif(angle_test,(*this).commande_f(angle_test));

      if ((voilier.contrainte_commande.first >= ma_commande) or (ma_commande >= voilier.contrainte_commande.second))
      {
        cout << "Les commandes sont imcompatibles avec le voilier" << endl; exit(1);
      }

      angle_test += 5;
    }
  }

  // Annonce si les commandes sont compatibles avec le voilier
  cout << "Les commandes sont compatibles avec le voilier" << endl;
}

#endif