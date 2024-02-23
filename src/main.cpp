#include <iostream>
#include "utilitaire.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello world!" << std::endl;

    //test vecteur
    cout << vecteur({1,2,3}) << endl;
    

    //test bi_vecteur
    vecteur<int> A({1,2,3});
    vecteur<int> B({1,2,4});
    cout << A << endl;
    bi_vecteur<int> champs(A,B);
    cout << champs << endl;
    champs.pushback(pair(8,9));
    cout << champs << endl;

    // A=B;
    // cout << A;

    //test route
    bi_vecteur<int> pos(B,A);
    route<int> route1(pair(1,3), pos, champs);
    cout << route1.position << endl;

    //test commande
    string fun = "cos";
    commande<int, float> com(fun, A);
    cout << com.vecteur_commande << endl;
    string chemin = "include/test.csv";

    //test polaire
    polaire<float> pol(chemin, ';');
    cout << pol.ligne_colonne << endl;
    cout << pol.vitesse_voilier << endl;
}

