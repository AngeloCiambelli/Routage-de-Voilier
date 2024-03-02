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
// Note: Pour les fonctions sans template les implémentation sont ajoutées dans 
// un fichier .cpp?
//
// Code inspipré de https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
//
//===========================================================================
//                            CSV vers tableau
//===========================================================================

// csv to string, 
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

template <typename T>
vecteur<vecteur<T>> csv_vers_table(const string& chemin, char sep)
{
  string contenu = fichier_vers_string(chemin); // contenu du .csv en string
  istringstream sstream(contenu);              // conversion du contenu en "stream" type pour utiliser la fonction getline()
  vecteur<T> element;                          // element de la ligne entiere
  string memoire;                              // element entre chaque séparateur normalement "espace nombre espace"
  vecteur<vecteur<T>> tableFinale;             // store the element

  // Compteur du numero de la ligne
  int compteur = 0;

  // Pour toutes les lignes
  while (getline(sstream, memoire))
  {
    // transformer la ligne en type "stream" necessaire pour getline()
    istringstream ligne(memoire);

    // trouver tous les elements de chaques lignes
    while (getline(ligne, memoire, sep))
    {
      // Nettoyer les elements des espaces autour
      memoire.erase(std::remove_if(memoire.begin(), memoire.end(), [](unsigned char x){ return std::isspace(x); }),memoire.end());
      
      // Convertir le type string dans le type T
      T memoire_type_T;
      istringstream(memoire) >> memoire_type_T;
      element.push_back(memoire_type_T);
    }

    // Remplir le tableau de valeur des polaires du voilier
    tableFinale.push_back(element);

    // Nettoyer les variables
    element.clear();
    compteur += 1;
  };
  return (tableFinale);
};

//===========================================================================
//                            Tableau vers CSV
//===========================================================================

template<typename T>
void exportToCSV(const vecteur<vecteur<T>>& data, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    for (const auto& row : data) {
        for (auto it = row.begin(); it != row.end(); ++it) {
            file << *it;
            if (it != row.end() - 1) {
                file << ',';
            }
        }
        file << endl;
    }

    file.close();
};

#endif