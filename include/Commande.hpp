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

  void verification_commande(const Voilier<float, float> &voilier)
  {
    if (stockage=="tabule")
    {
      for (int i=0; i<(*this).vecteur_commande.size()-1; i++)
      {
        //verifier que les commandes ne change pas trop entre chaque pas de temps
        if (voilier.contrainte_commande.first <= angle_relatif((*this).vecteur_commande[i],(*this).vecteur_commande[i+1]) <= voilier.contrainte_commande.second){}
        else {cout << "Les commandes sont imcompatibles avec le voilier" << endl; exit(1);}
      }
    }

    else if (stockage=="analytique")
    {
      float angle_test = -180;
      while (angle_test <= 180)
      {
        //Remplacer si besoin les commandes autorisé par le voilier
        if (voilier.contrainte_commande.first <= angle_relatif(angle_test,(*this).commande_f(angle_test)) <= voilier.contrainte_commande.second){}
        else {cout << "Les commandes sont imcompatibles avec le voilier" << endl; exit(1);}

        angle_test += 5;
      }
    }

    cout << "Les commandes sont compatibles avec le voilier" << endl;
  }
};

#endif