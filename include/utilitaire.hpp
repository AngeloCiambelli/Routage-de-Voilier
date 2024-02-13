#ifndef DEF_UTILITAIRE_HPP
#define DEF_UTILITAIRE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include "io.hpp"

using namespace std;

//===========================================================================
//                          vecteur
//===========================================================================

//On utilise la classe vector de la stl

template<typename T>
class vecteur : public vector<T>
{
public:
  vecteur(int d=0, const T& v0=T())  : vector<T> (d,v0) {}   // dim et composantes constantes
  vecteur(const initializer_list<T>& vs) : vector<T> (vs){} // depuis une liste explicite

  T  operator ()(int i) const { return this->at(i-1);} // valeur    1->dim (indice non testé)
  T& operator ()(int i) { return this->at(i-1);}       // référence 1->dim (indice non testé)

  vecteur<T>& operator +=(const vecteur<T>& v)
  {
    int n = (*this).size();
    if (n != v.size()) {cout << "hop hop hop ils n'ont pas la meme taille tes vecteurs"; exit(1);} 

    for (int i=0; i<n; i++)
    {
      (*this)[i]+=v[i];
    }
    return *this;
  } // u += v
  vecteur<T>& operator -=(const vecteur<T>& v)
  {
    int n = (*this).size();
    if (n != v.size()) {cout << "hop hop hop ils n'ont pas la meme taille tes vecteurs"; exit(1);} 

    for (int i=0; i<n; i++)
    {
      (*this)[i]-=v[i];
    }
    return *this;
  } // u -= v
  vecteur<T>& operator +=(const T& x)
  {
    int n = (*this).size();
    vecteur<T> a(n,x);

    (*this)+=a;

    return *this;
  } // u += x
  vecteur<T>& operator -=(const T& x)  
  {
    int n = (*this).size();
    vecteur<T> a(n,x);

    (*this)-=a;

    return *this;
  } // u -= x
  vecteur<T>& operator *=(const T& x)
  {
    int n = (*this).size();

    for (int i=0; i<n; i++)
    {
      (*this)[i]*=x;
    }

    return *this;
  } // u *= x
  vecteur<T>& operator /=(const T& x)
  {
    int n = (*this).size();

    for (int i=0; i<n; i++)
    {
      (*this)[i]/=x;
    }

    return *this;
  } // u /= x
}; // fin de définition de la classe

//functions externes
template<typename T>
ostream& operator <<(ostream& out,const vector<T>& v)
  {
    out << "[";
    for (int i=0; i<v.size(); i++)
    {
      if(i!=0) {out << ",";}
      out << v[i];
    }
    out << "]";
    return(out);
  };
template<typename T>
vecteur<T> operator +(const vecteur<T>& u, const vecteur<T>& v)
  {
    int n = u.size();
    if (n != v.size()) {cout << "hop hop hop ils n'ont pas la meme taille tes vecteurs"; exit(1);}

    vecteur<T> nouveau(n);

    for (int i=0; i<n; i++)
    {
      nouveau[i] = u[i]+v[i];
    }
    return nouveau;
  } // u + v
template<typename T>
vecteur<T> operator -(const vecteur<T>& u, const vecteur<T>& v)
  {
    return(u+(-v));
  } // u - v
template<typename T>
vecteur<T> operator +(const vecteur<T>& u){return u;} // +u
template<typename T>
vecteur<T> operator -(const vecteur<T>& u)
  {
    int n = u.size();
    vecteur<T> nouveau(n);

    for (int i=0; i<n; i++)
    {
      nouveau[i] = -u[i];
    }
    return nouveau;
  } // +u
template<typename T>
vecteur<T> operator +(const vecteur<T>& u, const T& x)
  {
    int n = u.size();
    vecteur<T> nouveau(n);
    vecteur<T> x_vector(n,x);

    nouveau = u+x_vector;
    return nouveau;
  } // u + x
template<typename T>
vecteur<T> operator -(const vecteur<T>& u, const T& x) {return u+(-x);} // u - x
template<typename T>
vecteur<T> operator *(const vecteur<T>& u, const T& x)
  {
    int n = u.size();
    vecteur<T> nouveau(n);

    for (int i=0; i<n; i++)
    {
      nouveau[i] = u[i]*x;
    }
    return nouveau;
  } // u * x
template<typename T>
vecteur<T> operator *(const T& x, const vecteur<T>& u) {return u*x;} // x*u
template<typename T>
vecteur<T> operator /(const vecteur<T>& u, const T& x)
  {
    int n = u.size();
    vecteur<T> nouveau(n);

    for (int i=0; i<n; i++)
    {
      nouveau[i] = u[i]/x;
    }
    return nouveau;
  } // u / x


//===========================================================================
//                          bi-vecteur
//===========================================================================

template<typename T>
class bi_vecteur
{
  public:
    vecteur<T> X;
    vecteur<T> Y;
    bi_vecteur(const vecteur<T>& _X,const vecteur<T>& _Y){X = _X; Y = _Y;};
    bi_vecteur(){X={}; Y={};};
    pair<T,T> operator [](const int& i) const{return pair((*this).X[i],(*this).Y[i]);};
    bi_vecteur<T>& operator =(const bi_vecteur<T>& vect){this->X = vect.X; this->Y = vect.Y; return *this;};
    bi_vecteur<T>& pushback(pair<T,T> xy){(this->X).push_back(xy.first); (this->Y).push_back(xy.second); return *this;}      
};

//fonctions externes
template<typename T>
ostream& operator <<(ostream& out,const bi_vecteur<T>& v)
{ 
  out << "[" << v.X << "," << v.Y << "]";
  return(out);
};

//===========================================================================
//                          route
//===========================================================================

template<typename T>
class route
{
  public :
    pair<T,T> depart;
    bi_vecteur<T> position;
    bi_vecteur<T> vitesse;

    route(pair<T,T> _depart, bi_vecteur<T> _position, bi_vecteur<T> _vitesse): position(), vitesse(){depart = _depart; position = _position; vitesse = _vitesse;}
};

//===========================================================================
//                          commande
//===========================================================================

template<typename T1, typename T2>
class commande
{
  public :
    vecteur<T2> vecteur_commande;
    string nom_fonction;

    commande(string fonction, vecteur<T1> delta_t)
    {
      nom_fonction = fonction;
      if (fonction=="cos"){for (int i=0; i<size(delta_t); i++){vecteur_commande.push_back(cos(delta_t[i]));};}
      if (fonction=="sin"){for (int i=0; i<size(delta_t); i++){vecteur_commande.push_back(sin(delta_t[i]));};}
      if (fonction=="constant"){for (int i=0; i<size(delta_t); i++){int c = 3; vecteur_commande.push_back(c*delta_t[i]);};}
      if (fonction==""){for (int i=0; i<size(delta_t); i++){vecteur_commande.push_back(0*delta_t[i]);};}
    }
};

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