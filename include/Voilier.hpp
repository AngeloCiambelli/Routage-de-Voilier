#ifndef DEF_VOILIER_HPP
#define DEF_VOILIER_HPP

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
#include "Polaire.hpp"
#include "Foncteur.hpp"
#include "Fonction_externes.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe de stockage des caractéristiques du Voilier.
//
// Note: Pas de fichier cpp a cause des templates
//
//===========================================================================
//                            Defnition de la classe Voilier
//===========================================================================

template <typename T1, typename T2>
class Voilier
{
public:
  pair<T1, T1> contrainte_commande; // (borne sup, borne inf) des actions de la commande
  polaire<T2> polaire_voilier;

  Voilier(const pair<T1, T1> &contraintes, const string &chemin, const char &sep);
  Voilier(const pair<T1, T1> &contraintes, const foncteur_polaire &f_polaire);
  Voilier(){};

  float V_b(const float &angle_bateau, const float &vitesse_vent) const;
};

template <typename T1, typename T2>
Voilier<T1, T2>::Voilier(const pair<T1, T1> &contraintes, const string &chemin, const char &sep) : polaire_voilier(chemin, sep, "tabule") { contrainte_commande = contraintes;}

template <typename T1, typename T2>
Voilier<T1, T2>::Voilier(const pair<T1, T1> &contraintes,  const foncteur_polaire &f_polaire) : polaire_voilier(f_polaire, "analytique") { contrainte_commande = contraintes;}

template <typename T1, typename T2>
float Voilier<T1,T2>::V_b(const float &angle_bateau_vent, const float &vitesse_vent) const
{
  float vitesse_bateau;
  // cout << angle_bateau_vent << vitesse_vent << endl <<endl;

  if ((*this).polaire_voilier.methode_stockage == "analytique") 
  {
    vitesse_bateau = (*this).polaire_voilier.polaire_analytique(angle_bateau_vent,vitesse_vent);
  }

  else if ((*this).polaire_voilier.methode_stockage == "tabule")
  {
    int indice_vitesse_1=0; int indice_vitesse_2=0;
    int indice_angle_1=0; int indice_angle_2=0;

    for (int i=0; i<((*this).polaire_voilier.polaire_tabule_entete.Y).size(); i++)
    {
      if((*this).polaire_voilier.polaire_tabule_entete.Y[i]<=vitesse_vent and (*this).polaire_voilier.polaire_tabule_entete.Y[i+1]>=vitesse_vent)
      {
        indice_vitesse_1 = i; indice_vitesse_2 = i+1;
      };
    }

    // cout << (*this).polaire_voilier.polaire_tabule_entete.X;

    for (int i=0; i<((*this).polaire_voilier.polaire_tabule_entete.X).size(); i++)
    {
      if((*this).polaire_voilier.polaire_tabule_entete.X[i]<=angle_bateau_vent and (*this).polaire_voilier.polaire_tabule_entete.X[i+1]>=angle_bateau_vent)
      {
        indice_angle_1 = i; indice_angle_2 = i+1;
      };
    }

    bi_vecteur indices(vecteur<int>({indice_angle_1,indice_angle_1,indice_angle_2,indice_angle_2}), 
                       vecteur<int>({indice_vitesse_1,indice_vitesse_2,indice_vitesse_1,indice_vitesse_2}));

    //Appeler l'interpolation
    vitesse_bateau = interpolation(indices, angle_bateau_vent, vitesse_vent,(*this).polaire_voilier.polaire_tabule_valeur);
  }
  return(vitesse_bateau);
}

#endif