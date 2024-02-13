#include <iostream>
#include <math.h>
#include "optimisation.hpp"


// grille::grille(int X, int Y, int T, float res, float p){
//     vecteur<vecteur<vecteur<float>>> tmp(
//         T,
//         vecteur<vecteur<float>>(
//         Y,
//         vecteur<float>(X)
//         ));
//     taille_X =  X;
//     taille_Y = Y;
//     Temps = T;
//     resolution = res;
//     pas = p;
//     score = tmp;
// }

// bi_vecteur<int> grille::localisation(float x, float y){
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