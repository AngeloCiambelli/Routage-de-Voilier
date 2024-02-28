#ifndef DEF_OPTIMISATION_HPP
#define DEF_OPTIMISATION_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "utilitaire.hpp"

using namespace std;


// class Flux{
//     public:
//     HJB solution;
//     dynamique fonction;
//     float calcul(vecteur<float> u, float i, float j, int n){
//         vecteur<float> xij;
//         xij[0] = i*solution.v.pas;
//         xij[1] = j*solution.v.pas;
//         vecteur<float> f = fonction(xij, u);
//         if(float(int(i))==i){
//             if(f[1]>0){
//                 return f[1]*solution.v(n,int(i),int(j)+1);
//             }
//             else{
//                 return f[1]*solution.v(n,int(i),int(j));
//             }
//         }
//         else{
//             if(f[0]>0){
//                 return f[0]*solution.v(n,int(i)+1,int(j));
//             }
//             else{
//                 return f[0]*solution.v(n,int(i),int(j));
//             }
//         }
//     }

// };



class HJB{
    public:
    Grille<float> v;
    HJB(int X, int Y, int Time, float res, float p);
    void resolve(Grille<float> v0);
};


HJB::HJB(int X, int Y, int Time, float res, float p){
    Grille<float> tmp(X, Y, Time, res, p);
    v = tmp;
}

void HJB::resolve(Grille<float> v0){
    
}

#endif