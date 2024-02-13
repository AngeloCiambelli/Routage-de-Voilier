#ifndef DEF_IO_HPP
#define DEF_IO_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include "utilitaire.hpp"

using namespace std;

//csv to string, code https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
string fichier_vers_string(const string& chemin);


// template<typename T>
// class polaire
// {
//   public:
//   bi_vecteur<string> ligne_colonne;
//   vecteur<vecteur<T>> vitesse_voilier;

//   polaire(const string& chemin, char separateur) //inspiré code https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
//   {
//     string contenu = fichier_vers_string(chemin); // contenu du .csv en string
//     istringstream sstream(contenu); // conversion du contenu en "stream" type pour utiliser la fonction getline()
//     std::vector<string> element; //element de la ligne entiere
//     string memoire; // element entre chaque séparateur normalement "espace nombre espace"

//     //Compteurs pour savoir dans quelle ligne on est 
//     int compteur_1 = 0;
   

//     while (std::getline(sstream, memoire)) // Pour toutes les lignes
//     {

//       istringstream ligne(memoire); //transformer la ligne en type "stream" necessaire pour getline()
      
//       // A quel élément de la ligne (compteur_2) on est.
//       int compteur_2 = 0;


//       while (std::getline(ligne, memoire, separateur)) { //trouver tous les elements de chaques lignes
//         if (compteur_2==0)  // Ajouter  dans le bi_vecteur des noms des lignes ou le tableau des valeurs
//         {
//           ligne_colonne.X.push_back(memoire);
//         }
//         else 
//         {
//           memoire.erase(remove_if(memoire.begin(), memoire.end(), isspace), memoire.end());
//           element.push_back(memoire);
//         }
//       }
//     // Ajouter l'element dans le bi_vecteur contenant les noms des colonnes ou dans le table de valeur
//     //if (compteur_1==0){ligne_colonne.Y = element;}
//     // else {vitesse_voilier.push_back(element);}

//     //Nettoyer les variables
//     element.clear();
//     compteur_1 += 1;
//     }
//   };
// };

// template<typename T>
// class voilier
// {
//   public:
//   pair<T, T> contrainte_commande;  // (borne sup, borne inf) des actions de la commande
//   polaire polaire_voilier;
// };

#endif