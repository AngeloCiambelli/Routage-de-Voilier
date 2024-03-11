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
  pair<T1, T1> contrainte_commande;   // Contraintes sur l'angle relatif (borne sup, borne inf)
  Polaire<T2>  polaire_voilier;       // Polaire du voilier (Vitesse en fonction de l'angle du bateau)

  // Constructeurs
  Voilier(const pair<T1, T1> &contraintes, const string &chemin, const char &sep);
  Voilier(const pair<T1, T1> &contraintes, const Foncteur_polaire &f_polaire);
  Voilier(){};

  // Fonctions membres
  float V_b(const float &angle_bateau, const float &vitesse_vent) const; // Vitesse du bateau en fonction de l'angle du vent 
                                                                         // par rapport à l'angle bateau
};

//===========================================================================
//                            Fonctions membres
//===========================================================================

template <typename T1, typename T2>
Voilier<T1, T2>::Voilier(const pair<T1, T1> &contraintes, const string &chemin, const char &sep) : polaire_voilier(chemin, sep, "tabule") 
{ 
  contrainte_commande = contraintes;
};

template <typename T1, typename T2>
Voilier<T1, T2>::Voilier(const pair<T1, T1> &contraintes,  const Foncteur_polaire &f_polaire) : polaire_voilier(f_polaire, "analytique") 
{ 
  contrainte_commande = contraintes;
};

template <typename T1, typename T2>
float Voilier<T1,T2>::V_b(const float &angle_bateau_vent, const float &vitesse_vent) const
{
  // Creation de la variable a retourner
  float vitesse_bateau;

  // Calcul de la vitesse du bateau de manière analytique
  if ((*this).polaire_voilier.stockage == "analytique") 
  {
    vitesse_bateau = (*this).polaire_voilier.analytique(angle_bateau_vent,vitesse_vent);
  }

  // Calcul de la vitesse du bateau via interpolation sur le tableau des polaires
  else if ((*this).polaire_voilier.stockage == "tabule")
  {
    // Trouver les quatres indices les plus proches de nos valeurs de vitesse du vent 
    // et d'angle du bateau dans le tableau des polaires 
    int indice_vitesse_1=0; int indice_vitesse_2=0;
    int indice_angle_1=0; int indice_angle_2=0;

    for (int i=0; i<((*this).polaire_voilier.entete.Y).size(); i++)
    {
      if((*this).polaire_voilier.entete.Y[i]<=vitesse_vent and 
        (*this).polaire_voilier.entete.Y[i+1]>=vitesse_vent)
      {
        indice_vitesse_1 = i; indice_vitesse_2 = i+1;
      };
    }

    for (int i=0; i<((*this).polaire_voilier.entete.X).size(); i++)
    {
      if((*this).polaire_voilier.entete.X[i]<=angle_bateau_vent and 
        (*this).polaire_voilier.entete.X[i+1]>=angle_bateau_vent)
      {
        indice_angle_1 = i; indice_angle_2 = i+1;
      };
    }

    Bi_vecteur indices(Vecteur<int>({indice_angle_1,indice_angle_1,indice_angle_2,indice_angle_2}), 
                       Vecteur<int>({indice_vitesse_1,indice_vitesse_2,indice_vitesse_1,indice_vitesse_2}));

    // Interpoler la vitesse du bateau à l'aide d'une moyenne à poid des quatres points 
    vitesse_bateau = interpolation(indices, 
                                  (*this).polaire_voilier.entete, 
                                  angle_bateau_vent, 
                                  vitesse_vent,
                                  (*this).polaire_voilier.table_valeur);
  }

  return(vitesse_bateau);
}

#endif