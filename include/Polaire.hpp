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
class Polaire
{
public:
  Bi_vecteur<float>   entete;         // Entêtes du tableau des polaires, X: Nom des lignes (Angle bateau % Angle vent), Y: Nom des colonnes (Vitesse vent)
  Vecteur<Vecteur<T>> table_valeur;   // Valeurs du tableau des polaires.
  Foncteur_polaire    analytique;     // Foncteur Polaire définissant les polaires de manière analytique
  string              stockage;       // Méthode de stockage employé

  // Constructeurs
  Polaire(const string &chemin, char separateur,const string& stockage);
  Polaire(const Foncteur_polaire& f_polaire, const string& stockage);
  Polaire();
};

template <typename T>
Polaire<T>::Polaire(const string &chemin, char separateur, const string &sto) // inspiré du code https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
{
  // Retenir qu'on stocke les informations de manière tabulée
  stockage = sto;

  string contenu = fichier_vers_string(chemin); // Contenu du .csv en string
  istringstream sstream(contenu);               // Conversion du contenu en "stream" type pour utiliser la fonction getline()
  
  // Variable qui acceuillent ce qu'on importe
  Vecteur<T> element;                           // Element de la ligne entiere
  string memoire;                               // Element entre chaque séparateur ','. Normalement on obtient "espace nombre espace"
  int compteur_1 = 0;                           // Compteurs de ligne

  // Pour toutes les lignes
  while (getline(sstream, memoire)) 
  {
    istringstream ligne(memoire);               // transformer la ligne en type "stream" necessaire pour getline()
    int compteur_2 = 0;                         // Compteur d'element de la ligne

     // Pour tous les elements de la ligne
    while (std::getline(ligne, memoire, separateur))
    { 
      // Nettoyer l'element memoire de possible espace autour de la valeur                                           
      memoire.erase(remove_if(memoire.begin(), memoire.end(), [](unsigned char x){ return isspace(x); }),memoire.end());

      // Ajouter dans le Bi_vecteur.X les noms des lignes 
      if ((compteur_2 == 0) && (compteur_1 != 0)) 
      {
        // Convertir le type string en float
        float memoire_float;
        istringstream(memoire) >> memoire_float; 
        (entete.X).push_back(memoire_float);
      }

      // Ajouter dans Bi_vecteur.Y le nom des colonnes ou dans la table des valeurs les valeurs des polaires
      else
      { 
        // Ajouter le nom de la colonne dans B_vecteur.Y 
        if ((compteur_1 == 0) && (compteur_2 != 0)) 
        {
          // Convertir le type string en float
          float memoire_float;
          istringstream(memoire) >> memoire_float; 
          (entete.Y).push_back(memoire_float);
        }

        // Ajouter la valeur dans la ligne d'element qui sera ensuite ajouté dans la table des valeurs
        else
        {
          // Convertir le type string dans le type T
          T memoire_T;
          istringstream(memoire) >> memoire_T; 
          element.push_back(memoire_T);
        }
      }
      compteur_2 += 1;
    }

    // Remplir le tableau de valeur des polaires du voilier
    if (compteur_1 != 0) 
    {
      table_valeur.push_back(element);
    }

    element.clear(); // Nettoyer les variables
    compteur_1 += 1; // Passe à la prochaine ligne
  }
};

template <typename T>
Polaire<T>::Polaire(const Foncteur_polaire& f_polaire, const string& sto)
{
  stockage = sto;
  analytique = f_polaire;
}

template <typename T>
Polaire<T>::Polaire() : entete(), table_valeur(), stockage(){}

#endif