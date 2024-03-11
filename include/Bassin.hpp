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
// Classe Bassin pour créer un bassin rectangulaire et stocker une grille du 
// bassin, et les champs de vents et de courants de facon analytique ou tabulée. 
// Ils sont issues par des fonctions de chaque emplacement de la grille, en 
// utilisant Foncteur_courant et Foncteur_vent provenant de Foncteurs.hpp.
//
// Note: 
//
//===========================================================================
//                 Definition de la classe Bassin
//===========================================================================

class Bassin
{
public:
  pair<float, float>      coin_bas_gauche;  // Coin en bas a gauche du rectangle bassin
  pair<float, float>      coin_haut_droit;  // Coin en haut a droite du rectangle bassin
  Grille                  grille;           // Grille du bassin
  Bi_vecteur<float>       champs_vent;      // Champs de vent stocké dans un bi_vecteur
  Bi_vecteur<float>       champs_courant;   // Champs de courant stocké dans un bi_vecteur
  Foncteur_vent           fonction_vent;    // Fonction vent qui prend un emplacement de la grille et renvoit le vent
  Foncteur_courant        fonction_courant; // Fonction courant qui prend un emplacement de la grille et renvoit le courant
  string                  stockage;         // Manière de stockage

  // Constructeurs
  Bassin(const pair<float, float> &a, const pair<float, float> &b, const float &pas,const Foncteur_vent &f_vent,const Foncteur_courant &f_courant, const string &s);
  Bassin();
};

//===========================================================================
//                 Fonctions membres
//===========================================================================

Bassin::Bassin(const pair<float, float> &a, const pair<float, float> &b, const float &pas,const Foncteur_vent &f_vent,const Foncteur_courant &f_courant, const string &s)
{
  // Remplissage des variables de l'objet bassin
  coin_bas_gauche = a;
  coin_haut_droit = b;
  stockage = s;
  fonction_vent = f_vent;
  fonction_courant = f_courant;
  grille = Grille(abs(b.first - a.first), abs(b.second - a.second), 1.f, 1.f, pas); // Construction de la grille
  champs_vent = Bi_vecteur<float>();
  champs_courant = Bi_vecteur<float>();

  // Si on veut stocker les champs de vent et courant de manière tabulée, on rempli champs_vents et champs_courants
  if (s == "tabule")
  {
    champs_vent = Bi_vecteur<float>();
    champs_courant = Bi_vecteur<float>();  
    
    for (int i = 0; i <= grille.taille_Y/grille.pas; i++)
    {
      for (int j = 0; j <= grille.taille_X/grille.pas; j++)
      {
        champs_vent.pushback(f_vent(float(j)*pas, float(i)*pas));
        champs_courant.pushback(f_courant(float(j)*pas, float(i)*pas));
      }
    }
  }
};

Bassin::Bassin() : champs_vent(), champs_courant()
{
  coin_bas_gauche = pair(0, 0);
  coin_haut_droit = pair(0, 0);
};

#endif