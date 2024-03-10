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
#include "Flux.hpp"
#include "HJB.hpp"
#include "route_optimale.hpp"

//===========================================================================
//                            Description
//===========================================================================
//
// On prend une grille de [0,10]x[0,10] avec un pas de 0.5
// Le bassin et defini avec les fonctions dans foncteur f_vent et f_courant
// Dans l'état tel quel le voilier a des polaires qui viennent de test.csv 
// PS : le bateau aiment pas beaucoup allez dans des direction differentes du vent

// Les vecteurs de courant et vent sont aussi stocké de maniere tabulé.

// Dans la simulation on fait 50 pas avec un pas de temps de 0.1 (Attention le bateau va vite!)


int main(int argc, char *argv[])
{
    // cout << "Hello world!" << std::endl;

    // //test vecteur
    // cout << vecteur({1,2,3}) << endl;

    // //test bi_vecteur
    // vecteur<float> A({1,2,3});
    // vecteur<float> B({1,2,4});
    // cout << A << endl;
    // bi_vecteur<float> champs(A,B);
    // cout << champs << endl;
    // float a=8;
    // float b=9;
    // champs.pushback(vecteur({a,b}));
    // cout << champs << endl;

    //test route
    vecteur<float> x_start(0);
    vecteur<float> y_start(0);
    bi_vecteur<float> pos(x_start,y_start);
    bi_vecteur<float> vit(x_start,y_start);
    route<float> route1(vecteur<float>({0.01, 0.01}), vecteur<float>({0,1}), pos, vit);
    cout << route1.position << endl;
    cout << route1.vitesse << endl << endl;
    //test commande
    foncteur_commande fun;
    Commande com(fun);
    cout << com.commande_f(1) << endl << endl;

    // //test polaire
    string chemin = "include/test.csv";
    // polaire<float> pol(chemin, ';', "tabule");
    // cout << pol.polaire_tabule_entete << endl;
    // cout << pol.polaire_tabule_valeur << endl << endl;

    //test voilier
    pair<float, float> min_max_com(-80,80); 
    foncteur_polaire polaire_analytique;
    //Voilier<float, float> voilier_the_first(min_max_com, chemin, ';');
    Voilier<float, float> voilier_the_first(min_max_com, polaire_analytique);
    // cout << voilier_the_first.polaire_voilier.vitesse_voilier << endl << endl;

    //Verification des commandes pour le voilier de bob
    com.verification_commande(voilier_the_first);
    
    //test Bassin
    foncteur_vent f;
    foncteur_courant g;
    
    float pas = 0.5;
    pair<float, float> bas(0,0);
    pair<float, float> haut(10,10);
    string sto("tabule"); //"tabule"
    Bassin bassin1(bas,haut,pas,f,g,sto);
    Bassin bassin2();
    
    // Exporter les données de champs de vent et courant pour l'affichage python
    // table_vers_csv(bi_vecteur_vers_table(bassin1.champs_vent, bassin1.grille)[0].first, "output/X_vent");
    // table_vers_csv(bi_vecteur_vers_table(bassin1.champs_vent, bassin1.grille)[0].second, "output/Y_vent");
    // table_vers_csv(bi_vecteur_vers_table(bassin1.champs_courant, bassin1.grille)[0].first, "output/X_courant");
    // table_vers_csv(bi_vecteur_vers_table(bassin1.champs_courant, bassin1.grille)[0].second, "output/Y_courant");

    // //test csv vers tableau
    // string chemin_tableau = "include/test_tableau.csv";
    // vecteur<vecteur<float>> test = csv_vers_table<float>(chemin_tableau, ';');
    // // cout << test << endl;

    // //test data export
    // // vecteur<pair<vecteur<vecteur<float>>, vecteur<vecteur<float>>>> test_export = bi_vecteur_vers_table(bassin1.champs_vent, bassin1.grille);
    // // table_vers_csv<float>(test_export[0].first, "output/X_test");

    // //Test dynamique
    Dynamique_voile dynamique_test1(bassin1, voilier_the_first);
    // // cout << acos(route1.vitesse[0][0]/sqrt(route1.vitesse[0]|route1.vitesse[0]))*180/(atan(1)*4) << endl;
    // // dynamique_test1.f(vecteur<float>({0,0}),acos(route1.vitesse[0][0]/sqrt(route1.vitesse[0]|route1.vitesse[0]))*180/(atan(1)*4), 0, com);

    // //Test simulateur
    // Simulateur simulateur_test(0.1,50, com);
    // cout << simulateur_test.mise_en_route(route1, dynamique_test1).position<<endl;


    //=======================================Test ROUTAGE OPTIMAL===========================================//
    //Test Grille
    Grille grille(10.f,10.f,1.5f,0.1f,0.5f);
    // bi_vecteur<int> x = grille.localisation(0.601f,0.12f);
    // cout << x <<endl;

    // cout << grille.find(0.601f,0.12f,0)<<endl;

    // //Test interpolation
    // float y1 = 0.601f; float y2 = 0.12f; 
    // int zero = 0;
    vecteur<float> v0 = create_v0(grille);
    Grille grille_mod = grille;
    grille_mod.resolution = 20;
    print_grille(grille_mod, v0);
    // cout << interpolation<float, vecteur<float>>(x, y1, y2,zero, v0, grille) << endl;
    // cout << v0[grille.find(x.X[0], x.Y[0], 0)] << ", ";
    // cout << v0[grille.find(x.X[1], x.Y[1], 0)] << ", "<<endl;
    // cout << v0[grille.find(x.X[2], x.Y[2], 0)] << ", ";
    // cout << v0[grille.find(x.X[3], x.Y[3], 0)] << ", "<<endl;
    // cout << v0<< endl;
    //Test Flux
    Dynamique_voile fonction(bassin1, voilier_the_first);
    // Flux flux(grille, fonction);
    // cout << flux.calcul(0, 5.5, 6, 0, v0)<< endl;

    //Test HJB
    // HJB HJB(v0,grille, fonction);
    
    // print_grille(grille, HJB.v);
    // HJB.resolve(10);
    // print_grille(grille, HJB.v);

    //Test route optimale
    route_optimale route(grille, fonction, v0);
    vecteur<float> x0({1.,2.});
    commandes_discretes commandes = route.calcul(x0, 15);
    cout << route.positions<<endl;
    cout << commandes << endl;
    cout << "gg"<<endl;

}

