#ifndef DEF_POLAIRE_HPP
#define DEF_POLAIRE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"
#include "Fonction_csv.hpp"
#include "Foncteur.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe de stockage des données polaires.
//
// Note: Pas de fichier cpp a cause du template
//
//===========================================================================
//                            Definition de la classe Polaire
//===========================================================================

template <typename T>
class polaire
{
public:
  bi_vecteur<int> polaire_tabule_entete;
  vecteur<vecteur<T>> polaire_tabule_valeur;
  foncteur_polaire polaire_analytique;
  string methode_stockage;

  polaire(const string &chemin, char separateur,const string& stockage);
  polaire(const foncteur_polaire& f_polaire, const string& stockage);
  polaire();
};

template <typename T>
polaire<T>::polaire(const string &chemin, char separateur, const string &stockage) // inspiré code https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
{
  string contenu = fichier_vers_string(chemin); // contenu du .csv en string
  istringstream sstream(contenu);              // conversion du contenu en "stream" type pour utiliser la fonction getline()
  vecteur<T> element;                           // element de la ligne entiere
  string memoire;                              // element entre chaque séparateur normalement "espace nombre espace"
  int compteur_1 = 0;                          // Compteurs pour savoir dans quelle ligne on est
  methode_stockage = stockage;

  while (getline(sstream, memoire)) // Pour toutes les lignes
  {
    istringstream ligne(memoire); // transformer la ligne en type "stream" necessaire pour getline()
    int compteur_2 = 0; // A quel élément de la ligne (compteur_2) on est.

    while (std::getline(ligne, memoire, separateur)) // trouver tous les elements de chaques lignes
    {                                             
      if ((compteur_2 == 0) && (compteur_1 != 0)) // Ajouter  dans le bi_vecteur des noms des lignes ou le tableau des valeurs
      {
        int memoire_int;
        istringstream(memoire) >> memoire_int; // Convertir le type string en entier
        (polaire_tabule_entete.X).push_back(memoire_int);
      }
      else
      {
        memoire.erase(remove_if(memoire.begin(), memoire.end(), [](unsigned char x){ return isspace(x); }),memoire.end()); // Nettoyer les elements des espaces autour

        if ((compteur_1 == 0) && (compteur_2 != 0)) // Ajouter l'element dans le bi_vecteur contenant les noms des colonnes ou dans le table de valeur
        {
          int memoire_int;
          istringstream(memoire) >> memoire_int; // Convertir le type string en entier
          (polaire_tabule_entete.Y).push_back(memoire_int);
        }

        else
        {
          T memoire_T;
          istringstream(memoire) >> memoire_T; // Convertir le type string dans le type T
          element.push_back(memoire_T);        // Ajouter cet element a la ligne d'element
        }
      }
      compteur_2 += 1;
    }

    if (compteur_1 != 0) // Remplir le tableau de valeur des polaires du voilier
    {
      polaire_tabule_valeur.push_back(element);
    }

    element.clear(); // Nettoyer les variables
    compteur_1 += 1;
  }
};

template <typename T>
polaire<T>::polaire(const foncteur_polaire& f_polaire, const string& stockage)
{
  methode_stockage = stockage;
  polaire_analytique = f_polaire;
}

template <typename T>
polaire<T>::polaire() : polaire_tabule_entete(), polaire_tabule_valeur(vecteur<T>()), methode_stockage(){}

#endif