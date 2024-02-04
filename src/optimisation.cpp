#include <iostream>
#include "optimisation.hpp"


grille::grille(int X, int Y, int T, float res, float p){
    vecteur<vecteur<vecteur<float>>> tmp(
        T,
        vecteur<vecteur<float>>(
        Y,
        vecteur<float>(X)
        ));
    resolution = res;
    pas = p;
}