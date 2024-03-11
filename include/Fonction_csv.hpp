#ifndef DEF_FONCTION_CSV_HPP
#define DEF_FONCTION_CSV_HPP

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
// Receuil des fonctions nécéssaires à l'import et l'export de fichier csv
//
// Code d'import inspiré de https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
//
//===========================================================================
//                            .csv vers tableau
//===========================================================================

// Fonction convertissant les .csv en string
string fichier_vers_string(const string &chemin)
{
  auto ss = ostringstream{};
  ifstream input_file(chemin);
  if (!input_file.is_open())
  {
    cerr << "impossible ouvrir le fichier - '" << chemin << "'" << endl;
    exit(1);
  }
  ss << input_file.rdbuf();
  return ss.str();
};

// Fonction qui importe un fichier .csv (sans entêtes) en table Vecteur<Vecteur<T>>
template <typename T>
Vecteur<Vecteur<T>> csv_vers_table(const string& chemin, char sep)
{
  // Import des données csv en "string" puis "istringstream"
  string contenu = fichier_vers_string(chemin); // Contenu du .csv en string
  istringstream sstream(contenu);               // Conversion du contenu en "stream" type pour utiliser la fonction getline()
  
  // Definition des variables
  Vecteur<T> element;                           // Element de la ligne entiere
  string memoire;                               // Element entre chaque séparateur normalement "espace nombre espace"
  Vecteur<Vecteur<T>> tableFinale;              // Table finale de stockage du csv

  // Compteur du numero de la ligne
  int compteur = 0;

  // Pour toutes les lignes
  while (getline(sstream, memoire))
  {
    // transformer la ligne en type "stream" necessaire pour getline()
    istringstream ligne(memoire);

    // Trouver tous les elements de chaques lignes
    while (getline(ligne, memoire, sep))
    {
      // Nettoyer les elements des espaces autour quand il y en a
      memoire.erase(std::remove_if(memoire.begin(), memoire.end(), [](unsigned char x){ return std::isspace(x); }),memoire.end());
      
      // Convertir le type string dans le type T
      T memoire_type_T;
      istringstream(memoire) >> memoire_type_T;
      element.push_back(memoire_type_T);
    }

    // Remplir le tableau de valeur ligne par ligne
    tableFinale.push_back(element);

    // Nettoyer les variables
    element.clear();
    compteur += 1;
  };
  return (tableFinale);
};

//===========================================================================
//                            Tableau vers .csv
//===========================================================================

// Fonction qui exporte une table Vecteur<Vecteur<T>> en .csv
template<typename T>
void table_vers_csv(const Vecteur<Vecteur<T>>& table, const string& chemin) 
{
  ofstream fichier(chemin);

  if (!fichier.is_open()) {
      cerr << "Ne peut pas ouvrir pour remplir " << chemin << endl;
      return;
  }

  for (const auto& ligne : table) {
      for (auto it = ligne.begin(); it != ligne.end(); ++it) {
          fichier << *it;
          if (it != ligne.end() - 1) {
              fichier << ',';
          }
      }
      fichier << endl;
  }

  fichier.close();
};

#endif