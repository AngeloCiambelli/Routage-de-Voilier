#ifndef DEF_FLUX_HPP
#define DEF_FLUX_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "Grille.hpp"
#include "Dynamique.hpp"
#include "Commande_discrete.hpp"

using namespace std;


// class Flux{
//     public:
//     Grille grille;
//     Dynamique_voile fonction;
//     Flux(const Grille g, const Dynamique_voile f): grille(g),fonction(f){};
//     float calcul(float u, float i, float j, int n, vecteur<float> v_prec){
//         vecteur<float> xij(2,i*grille.pas);
//         xij[1]=j*grille.pas;
//         vecteur<float> f = fonction.f(xij, u, n);
//         if(float(int(i))==i){
//             if(f[1]>0){
//                 return f[1]*v_prec[grille.find(int(j)+1,int(i),n-1)];
//             }
//             else{
//                 return f[1]*v_prec[grille.find(int(j),int(i),n-1)];
//             }
//         }
//         else{
//             if(f[0]>0){
//                 return f[0]*v_prec[grille.find(int(j),int(i)+1,n-1)];
//             }
//             else{
//                 return f[0]*v_prec[grille.find(int(j),int(i),n-1)];
//             }
//         }
//     }

// };

#endif

