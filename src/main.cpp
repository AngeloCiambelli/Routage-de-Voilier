#include "Vecteur.hpp"
#include "Bi_vecteur.hpp"
#include "Route.hpp"
#include "Commande.hpp"
#include "Polaire.hpp"
#include "Voilier.hpp"
#include "Foncteur.hpp"
#include "Bassin.hpp"
#include "Fonction_csv.hpp"

int main(int argc, char *argv[])
{
    cout << "Hello world!" << std::endl;

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
    cout << route1.position << endl << endl;

    //test commande
    string fun = "cos";
    commande<int, float> com(fun, A);
    cout << com.vecteur_commande << endl << endl;

    //test polaire
    string chemin = "include/test.csv";
    polaire<int> pol(chemin, ';');
    // cout << pol.ligne_colonne << endl;
    // cout << pol.vitesse_voilier << endl << endl;

    //test voilier
    pair<int, int> min_max_com(3,200);
    voilier<int, float> voilier_the_first(min_max_com, chemin, ';');
    // cout << voilier_the_first.polaire_voilier.vitesse_voilier << endl << endl;

    //test bassin
    foncteur_vent f;
    foncteur_courant g;
    
    float pas = 0.1;
    pair<float, float> bas(0,0);
    pair<float, float> haut(1,1);
    string sto("tableau");
    bassin bassin1(bas,haut,pas,f,g,sto);
    bassin bassin2();

    cout << endl << bassin1.champs_vent << endl << endl;
    // cout << endl << bassin1.champs_courant.valeur[0] << endl << endl;
    // cout << bassin1.champs_vent.separation().first << endl;

    //test csv vers tableau
    string chemin_tableau = "include/test_tableau.csv";
    vecteur<vecteur<float>> test = csv_vers_table<float>(chemin_tableau, ';');
    cout << test << endl;

    // //test data export
    // exportToCSV<float>(bassin1.champs_vent.separation().first, "output/X_test");
}

