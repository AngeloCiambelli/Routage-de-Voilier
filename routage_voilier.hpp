#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

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
        pair<vecteur<T>, vecteur<T>> XY;
        bi_vecteur(const vecteur<T>& X,const vecteur<T>& Y){XY.first=X; XY.second=Y;};
        pair<T,T> operator[](const int i) const{return pair((*this).XY.first[i],(*this).XY.second[i]);};
        //pair<T,T>& operator[](const int i){return pair((*this).XY.first[i],(*this).XY.second[i]);};
        bi_vecteur<T>& pushback(pair<T,T> xy){((*this).XY.first).push_back(xy.first); ((*this).XY.second).push_back(xy.second); return *this;}
};

//fonctions externes
template<typename T>
ostream& operator <<(ostream& out,const bi_vecteur<T>& v)
{ 
    out << "[" << v.XY.first << "," << v.XY.second << "]";
    return(out);
};




