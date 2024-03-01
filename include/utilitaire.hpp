#ifndef DEF_UTILITAIRE_HPP
#define DEF_UTILITAIRE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//===========================================================================
//                          vecteur
//===========================================================================

// On utilise la classe vector de la stl
template <typename T>
class vecteur : public vector<T>
{
public:
  vecteur(int d = 0, const T &v0 = T()) : vector<T>(d, v0) {} // dim et composantes constantes
  vecteur(const initializer_list<T> &vs) : vector<T>(vs) {}   // depuis une liste explicite

  T operator()(int i) const { return this->at(i - 1); } // valeur    1->dim (indice non testé)
  T &operator()(int i) { return this->at(i - 1); }      // référence 1->dim (indice non testé)

  vecteur<T> &operator+=(const vecteur<T> &v)
  {
    int n = (*this).size();
    if (n != v.size())
    {
      cout << "hop hop hop ils n'ont pas la meme taille tes vecteurs";
      exit(1);
    }

    for (int i = 0; i < n; i++)
    {
      (*this)[i] += v[i];
    }
    return *this;
  } // u += v
  vecteur<T> &operator-=(const vecteur<T> &v)
  {
    int n = (*this).size();
    if (n != v.size())
    {
      cout << "hop hop hop ils n'ont pas la meme taille tes vecteurs";
      exit(1);
    }

    for (int i = 0; i < n; i++)
    {
      (*this)[i] -= v[i];
    }
    return *this;
  } // u -= v
  vecteur<T> &operator+=(const T &x)
  {
    int n = (*this).size();
    vecteur<T> a(n, x);

    (*this) += a;

    return *this;
  } // u += x
  vecteur<T> &operator-=(const T &x)
  {
    int n = (*this).size();
    vecteur<T> a(n, x);

    (*this) -= a;

    return *this;
  } // u -= x
  vecteur<T> &operator*=(const T &x)
  {
    int n = (*this).size();

    for (int i = 0; i < n; i++)
    {
      (*this)[i] *= x;
    }

    return *this;
  } // u *= x
  vecteur<T> &operator/=(const T &x)
  {
    int n = (*this).size();

    for (int i = 0; i < n; i++)
    {
      (*this)[i] /= x;
    }

    return *this;
  } // u /= x
};  // fin de définition de la classe

// functions externes
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v)
{
  out << "[";
  for (int i = 0; i < v.size(); i++)
  {
    if (i != 0)
    {
      out << ",";
    }
    out << v[i];
  }
  out << "]";
  return (out);
};
template <typename T>
vecteur<T> operator+(const vecteur<T> &u, const vecteur<T> &v)
{
  int n = u.size();
  if (n != v.size())
  {
    cout << "hop hop hop ils n'ont pas la meme taille tes vecteurs";
    exit(1);
  }

  vecteur<T> nouveau(n);

  for (int i = 0; i < n; i++)
  {
    nouveau[i] = u[i] + v[i];
  }
  return nouveau;
} // u + v
template <typename T>
vecteur<T> operator-(const vecteur<T> &u, const vecteur<T> &v)
{
  return (u + (-v));
} // u - v
template <typename T>
vecteur<T> operator+(const vecteur<T> &u) { return u; } // +u
template <typename T>
vecteur<T> operator-(const vecteur<T> &u)
{
  int n = u.size();
  vecteur<T> nouveau(n);

  for (int i = 0; i < n; i++)
  {
    nouveau[i] = -u[i];
  }
  return nouveau;
} // +u
template <typename T>
vecteur<T> operator+(const vecteur<T> &u, const T &x)
{
  int n = u.size();
  vecteur<T> nouveau(n);
  vecteur<T> x_vector(n, x);

  nouveau = u + x_vector;
  return nouveau;
} // u + x
template <typename T>
vecteur<T> operator-(const vecteur<T> &u, const T &x) { return u + (-x); } // u - x
template <typename T>
vecteur<T> operator*(const vecteur<T> &u, const T &x)
{
  int n = u.size();
  vecteur<T> nouveau(n);

  for (int i = 0; i < n; i++)
  {
    nouveau[i] = u[i] * x;
  }
  return nouveau;
} // u * x
template <typename T>
vecteur<T> operator*(const T &x, const vecteur<T> &u) { return u * x; } // x*u
template <typename T>
vecteur<T> operator/(const vecteur<T> &u, const T &x)
{
  int n = u.size();
  vecteur<T> nouveau(n);

  for (int i = 0; i < n; i++)
  {
    nouveau[i] = u[i] / x;
  }
  return nouveau;
} // u / x

//===========================================================================
//                            CSV vers tableau
//===========================================================================

// csv to string, code https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
string fichier_ver_string(const string &chemin)
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
vecteur<vecteur<T>> csv_vers_table(string chemin, char sep)
{
  string contenu = fichier_ver_string(chemin); // contenu du .csv en string
  istringstream sstream(contenu);              // conversion du contenu en "stream" type pour utiliser la fonction getline()
  vecteur<T> element;                          // element de la ligne entiere
  string memoire;                              // element entre chaque séparateur normalement "espace nombre espace"
  vecteur<vecteur<T>> tableFinale;
  vecteur<string> entete;

  // Compteur du numero de la ligne
  int compteur = 0;

  while (getline(sstream, memoire)) // Pour toutes les lignes
  {
    istringstream ligne(memoire); // transformer la ligne en type "stream" necessaire pour getline()

    while (getline(ligne, memoire, sep)) // trouver tous les elements de chaques lignes
    {
      // Nettoyer les elements des espaces autour
      memoire.erase(std::remove_if(memoire.begin(), memoire.end(), [](unsigned char x){ return std::isspace(x); }),memoire.end());

      // Ajouter l'element dans le vecteur d'entête contenant les noms des colonnes ou dans le tableau de valeur
      if (compteur == 0)
      {
        entete.push_back(memoire);
      }

      else
      {
        T memoire_type_T;
        istringstream(memoire) >> memoire_type_T; // Convertir le type string dans le type T
        element.push_back(memoire_type_T);        // Ajouter cet element a la ligne d'element
      }
    }

    // Remplir le tableau de valeur des polaires du voilier
    if (compteur != 0)
    {
      tableFinale.push_back(element);
    }

    // Nettoyer les variables
    element.clear();
    compteur += 1;
  };
  return (entete, tableFinale);
};

//===========================================================================
//                            Tableau vers CSV
//===========================================================================

//===========================================================================
//                            bi-vecteur
//===========================================================================

template <typename T>
class bi_vecteur
{
public:
  vecteur<T> X;
  vecteur<T> Y;
  bi_vecteur(const vecteur<T> &_X, const vecteur<T> &_Y)
  {
    X = _X;
    Y = _Y;
  };
  bi_vecteur()
  {
    X = {};
    Y = {};
  };
  pair<T, T> operator[](const int &i) const { return pair((*this).X[i], (*this).Y[i]); };
  bi_vecteur<T> &operator=(const bi_vecteur<T> &vect)
  {
    this->X = vect.X;
    this->Y = vect.Y;
    return *this;
  };
  bi_vecteur<T> &pushback(pair<T, T> xy)
  {
    (this->X).push_back(xy.first);
    (this->Y).push_back(xy.second);
    return *this;
  }
};

// fonctions externes
template <typename T>
ostream &operator<<(ostream &out, const bi_vecteur<T> &v)
{
  out << "[" << v.X << "," << v.Y << "]";
  return (out);
};

//===========================================================================
//                            route
//===========================================================================

template <typename T>
class route
{
public:
  pair<T, T> depart;
  bi_vecteur<T> position;
  bi_vecteur<T> vitesse;

  route(pair<T, T> _depart, bi_vecteur<T> _position, bi_vecteur<T> _vitesse) : position(), vitesse()
  {
    depart = _depart;
    position = _position;
    vitesse = _vitesse;
  }
};

//===========================================================================
//                            commande
//===========================================================================

template <typename T1, typename T2>
class commande
{
public:
  vecteur<T2> vecteur_commande;
  string nom_fonction;

  commande(string fonction, vecteur<T1> delta_t)
  {
    nom_fonction = fonction;
    if (fonction == "cos")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        vecteur_commande.push_back(cos(delta_t[i]));
      };
    }
    if (fonction == "sin")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        vecteur_commande.push_back(sin(delta_t[i]));
      };
    }
    if (fonction == "constant")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        int c = 3;
        vecteur_commande.push_back(c * delta_t[i]);
      };
    }
    if (fonction == "")
    {
      for (int i = 0; i < size(delta_t); i++)
      {
        vecteur_commande.push_back(0 * delta_t[i]);
      };
    }
  }
};

//===========================================================================
//                            polaire
//===========================================================================

template <typename T>
class polaire
{
public:
  bi_vecteur<string> ligne_colonne;
  vector<vector<T>> vitesse_voilier;

  polaire(const string &chemin, char separateur); // inspiré code https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
};

template <typename T>
polaire<T>::polaire(const string &chemin, char separateur) // inspiré code https://www.delftstack.com/fr/howto/cpp/read-csv-file-in-cpp/
{
  string contenu = fichier_ver_string(chemin); // contenu du .csv en string
  istringstream sstream(contenu);              // conversion du contenu en "stream" type pour utiliser la fonction getline()
  vector<T> element;                           // element de la ligne entiere
  string memoire;                              // element entre chaque séparateur normalement "espace nombre espace"

  // Compteurs pour savoir dans quelle ligne on est
  int compteur_1 = 0;

  while (std::getline(sstream, memoire)) // Pour toutes les lignes
  {
    istringstream ligne(memoire); // transformer la ligne en type "stream" necessaire pour getline()

    // A quel élément de la ligne (compteur_2) on est.
    int compteur_2 = 0;

    while (std::getline(ligne, memoire, separateur))
    {                                             // trouver tous les elements de chaques lignes
      if ((compteur_2 == 0) && (compteur_1 != 0)) // Ajouter  dans le bi_vecteur des noms des lignes ou le tableau des valeurs
      {
        ligne_colonne.X.push_back(memoire);
      }
      else
      {
        // Nettoyer les elements des espaces autour
        memoire.erase(std::remove_if(memoire.begin(), memoire.end(), [](unsigned char x){ return std::isspace(x); }),memoire.end());

        // Ajouter l'element dans le bi_vecteur contenant les noms des colonnes ou dans le table de valeur
        if ((compteur_1 == 0) && (compteur_2 != 0))
        {
          (ligne_colonne.Y).push_back(memoire);
        }
        else
        {
          T memoire_float;
          istringstream(memoire) >> memoire_float; // Convertir le type string dans le type T
          element.push_back(memoire_float);        // Ajouter cet element a la ligne d'element
        }
      }
      compteur_2 += 1;
    }

    // Remplir le tableau de valeur des polaires du voilier
    // cout << element << endl;
    if (compteur_1 != 0)
    {
      vitesse_voilier.push_back(element);
    }

    // Nettoyer les variables
    element.clear();
    compteur_1 += 1;
  }
};

//===========================================================================
//                            voilier
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
voilier<T1, T2>::voilier(const pair<T1, T1> &contraintes, const string &chemin, const char sep) : polaire_voilier(chemin, sep) { contrainte_commande = contraintes; }

//===========================================================================
//                            grilles
//===========================================================================

template <typename T>
class Grille
{
public:
  int taille_X;
  int taille_Y;
  int Temps;
  float pas;
  float resolution;
  vecteur<vecteur<vecteur<T>>> valeur;

  Grille(int X, int Y, int Time, float res, float p);
  Grille(){};
  bi_vecteur<int> localisation(const float &x, const float &y);
  float operator()(int t, int j, int i)
  {
    if (i >= taille_X || j >= taille_Y)
    {
      cout << "Erreur : indices non-valides";
      exit(1);
    }
    return valeur[t][j][i];
  };
  T interpolation(const float &x, const float &y, const int &timestamp);
  pair<vecteur<vecteur<float>>, vecteur<vecteur<float>>> separation()
  {
    vecteur<vecteur<float>> X(this->taille_Y/this->pas, vecteur<float>(this->taille_X/this->pas));
    vecteur<vecteur<float>> Y(this->taille_Y/this->pas, vecteur<float>(this->taille_X/this->pas));

    for (int i = 0; i < this->taille_Y/this->pas; i++)
      {
        for (int j = 0; j <this->taille_X/this->pas; j++)
        {
          X[i][j] = (*this).valeur[0][i][j][0];
          Y[i][j] = (*this).valeur[0][i][j][1];
        }
      }
    return(pair(X,Y));
  };
};

template <typename T>
Grille<T>::Grille(int X, int Y, int Time, float res, float p)
{
  vecteur<vecteur<vecteur<T>>> tmp(
      Time / res,
      vecteur<vecteur<T>>(
          Y / p,
          vecteur<T>(X / p)));
  taille_X = X;
  taille_Y = Y;
  Temps = Time;
  resolution = res;
  pas = p;
  valeur = tmp;
};



// template<typename T>
// bi_vecteur<int> Grille<T>::localisation(const float &x, const float &y){
//     // rend les quatres indices des points ABCD correspondant au rectangle ABCD
//     // dans lequel se trouve le point de coordonnée (x,y) (A en bas gauche, D au-dessus de A)
//     vecteur<int> Xs(4);
//     vecteur<int> Ys(4);
//     Xs[0] = int(floor(x/resolution));
//     Ys[0] = int(floor(y/resolution));
//     Xs[1] = Xs[0] + 1;
//     Ys[1] = Ys[0];
//     Xs[2] = Xs[1];
//     Ys[2] = Ys[1] + 1;
//     Xs[3] = Xs[0];
//     Ys[3] = Ys[2];
//     bi_vecteur<int> result(Xs,Ys);
//     return result;
// }

// template<typename T>
// T Grille<T>::interpolation(const float &x, const float &y, const int &timestamp){
//   T sum = T();
//   bi_vecteur position = localisation(const float &x, const float &y);
//   float w11;float w12;float w21; float w22;
//   float x1;float x2;float y1; float y2;
//   x1 = position.X[0];x2 = position.X[2];
//   y1 = position.Y[0];y2 = position.Y[2];
//   float D = (x2-x1)(y2-y1);
//   w11 = (x2 - x)(y2 - y)/D;
//   w12 = (x2 - x)(y - y1)/D;
//   w21 = (x - x1)(y2 - y)/D;
//   w22 = (x - x1)(y - y1)/D;
//   sum = valeur[timestamp][y1][x1]*w11 + valeur[timestamp][y2][x1]*w21 + valeur[timestamp][y1][x2]*w12 + valeur[timestamp][y2][x2]*w22;
//   return sum;
// };

class commandes_discretes
{
public:
  vector<float> commandes;
  float contrainte;
  bool check_commandes()
  {
    float a = commandes[0];
    for (int i = 1; i < commandes.size(); i++)
    {
      if (fmod(abs(commandes[i] - a), 360.) > contrainte)
      {
        cout << "Erreur : commande invalide. Il y a un changment brusque de direction.";
      }
      a = commandes[i];
    }
  }
};

class dynamique
{
};

//===========================================================================
//                            bassin
//===========================================================================

// Functor pour definir analytiquement le champ de vent
class functor_vent
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur{sin(a), sin(b)};
  }
};

// Functor pour definir analytiquement le champ de courant
class functor_courant
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur{sin(a) + 1 / exp(a) * cos(b), sin(b) + 1 + 1 / (a + b + 1)};
  }
};

class bassin
{
public:
  pair<float, float> coin_bas_gauche;
  pair<float, float> coin_haut_droit;
  Grille<vecteur<float>> champs_vent;
  Grille<vecteur<float>> champs_courant;
  functor_vent fonction_vent;
  functor_courant fonction_courant;

  bassin(const pair<float, float> &a, const pair<float, float> &b, const float &pas, functor_vent &f_vent, functor_courant &f_courant, const string &stockage) : champs_vent(abs(a.first - b.first), abs(b.second - a.second), 1, 1, pas), champs_courant(abs(a.first - b.first), abs(b.second - a.second), 1, 1, pas)
  {
    coin_bas_gauche = a;
    coin_haut_droit = b;

    if (stockage == "analytique")
    {
      fonction_vent = f_vent;
      fonction_courant = f_courant;
      // /!\ Enregistre toujours le tableau mais on ne veut pas ça !
    }

    else if (stockage == "tableau")
    {
      //  A coder avec des append et utiliser le constructeur vide en haut
      for (int i = 0; i < (champs_vent.valeur[0]).size(); i++)
      {
        for (int j = 0; j < (champs_vent.valeur[0][i]).size(); j++)
        {
          champs_vent.valeur[0][i][j] = f_vent(i * pas, j * pas);
          champs_courant.valeur[0][i][j] = f_courant(i * pas, j * pas);
        }
      }
    }
  };

  bassin() : champs_vent(), champs_courant()
  {
    coin_bas_gauche = pair(0, 0);
    coin_haut_droit = pair(0, 0);
  };
};

#endif