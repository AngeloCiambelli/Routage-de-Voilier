#include "Vecteur.hpp"
#include "Bi_vecteur.hpp"
#include "Route.hpp"
#include "Commande.hpp"
#include "Polaire.hpp"
#include "Voilier.hpp"
#include "Foncteur.hpp"
#include "Bassin.hpp"
#include "Fonction_csv.hpp"
#include "Fonction_externes.hpp"
#include "Dynamique.hpp"
#include "Simulateur.hpp"

int main(int argc, char *argv[])
{
    cout << "Hello world!" << std::endl;

    //test vecteur
    cout << vecteur({1,2,3}) << endl;

    //test bi_vecteur
    vecteur<float> A({1,2,3});
    vecteur<float> B({1,2,4});
    cout << A << endl;
    bi_vecteur<float> champs(A,B);
    cout << champs << endl;
    float a=8;
    float b=9;
    champs.pushback(vecteur({a,b}));
    cout << champs << endl;

    // A=B;
    // cout << A;

    //test route
    vecteur<float> x_start(0);
    vecteur<float> y_start(0);
    bi_vecteur<float> pos(x_start,y_start);
    route<float> route1(vecteur<float>({0, 0}), vecteur<float>({0,1}), pos, champs);
    cout << route1.position << endl << endl;

    //test commande
    string fun = "cos";
    commande<float, float> com(fun, A);
    cout << com.vecteur_commande << endl << endl;

    //test polaire
    string chemin = "include/test.csv";
    polaire<float> pol(chemin, ';', "analytique");
    cout << pol.polaire_tabule_entete << endl;
    cout << pol.polaire_tabule_valeur << endl << endl;

    //test voilier
    pair<float, float> min_max_com(3,200);
    Voilier<float, float> voilier_the_first(min_max_com, chemin, ';');
    // cout << voilier_the_first.polaire_voilier.vitesse_voilier << endl << endl;

    //test Bassin
    foncteur_vent f;
    foncteur_courant g;
    
    float pas = 0.1;
    pair<float, float> bas(0,0);
    pair<float, float> haut(1,1);
    string sto("tabule");
    Bassin bassin1(bas,haut,pas,f,g,sto);
    Bassin bassin2();

    cout << endl << bassin1.champs_courant << endl << endl;
    cout << endl << bi_vecteur_vers_table(bassin1.champs_courant, bassin1.grille)[0].first << endl << endl;

    //test csv vers tableau
    string chemin_tableau = "include/test_tableau.csv";
    vecteur<vecteur<float>> test = csv_vers_table<float>(chemin_tableau, ';');
    cout << test << endl;

    //test data export
    vecteur<pair<vecteur<vecteur<float>>, vecteur<vecteur<float>>>> test_export = bi_vecteur_vers_table(bassin1.champs_vent, bassin1.grille);
    table_vers_csv<float>(test_export[0].first, "output/X_test");

    //Test dynamique
    Dynamique_voile dynamique_test1(bassin1, voilier_the_first);
    cout << acos(route1.vitesse[0][0]/sqrt(route1.vitesse[0]|route1.vitesse[0]))*180/(atan(1)*4) << endl;
    dynamique_test1.f(vecteur<float>({0,0}),acos(route1.vitesse[0][0]/sqrt(route1.vitesse[0]|route1.vitesse[0]))*180/(atan(1)*4), 0);

    //Test simulateur
    Simulateur simulateur_test(0.05,5);
    cout << simulateur_test.mise_en_route(route1, dynamique_test1).position;
    
}

