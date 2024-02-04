#include <iostream>
#include "optimisation.hpp"


grille::grille(int X, int Y, int T, float res, float p){
    vecteur<vecteur<vecteur<float>>> tmp(
        T,
        vecteur<vecteur<float>>(
        Y,
        vecteur<float>(X)
        ));
    taille_X =  X;
    taille_Y = Y;
    Temps = T;
    resolution = res;
    pas = p;
    score = tmp;
}

bi_vecteur<int> grille::localisation(float x, float y){
    // rend les quatres indices des points ABCD correspondant au rectangle ABCD
    // dans lequel se trouve le point de coordonnée (x,y)
    vecteur<int> Xs(4);
    vecteur<int> Ys(4);
    bi_vecteur<int> result(Xs,Ys);
    
}