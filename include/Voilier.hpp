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
#include "Polaire.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe de stockage des caractéristiques du voilier.
//
// Note: Pas de fichier cpp a cause des templates
//
//===========================================================================
//                            Defnition de la classe voilier
//===========================================================================

template <typename T1, typename T2>
class voilier
{
public:
  pair<T1, T1> contrainte_commande; // (borne sup, borne inf) des actions de la commande
  polaire<T2> polaire_voilier;
  voilier(const pair<T1, T1> &contraintes, const string &chemin, const char sep);
};

template <typename T1, typename T2>
voilier<T1, T2>::voilier(const pair<T1, T1> &contraintes, const string &chemin, const char sep) : polaire_voilier(chemin, sep) { contrainte_commande = contraintes;}

#endif