#ifndef DEF_ROUTE_OPTIMALE_HPP
#define DEF_ROUTE_OPTIMALE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"
#include "Fonction_externes.hpp"
#include "Commande_discrete.hpp"
#include "Dynamique.hpp"
#include "HJB.hpp"

using namespace std;

class route_optimale{
    private:
    commandes_discretes commandes;
    Grille grille;
    int max_iter = 1000;
    Dynamique_voile vitesse;
    HJB HJB_new;

    public:
    Bi_vecteur<float> positions;
    int n;

    route_optimale(Grille& g, Dynamique_voile& f, Vecteur<float>& v0):  // constructeur par défaut
    grille(g), vitesse(f), HJB_new(v0,g,f), max_iter(grille.Temps/grille.resolution), positions(){}

    int calcul_n(const Vecteur<float> &x0){ // calcul du nombre d'itération requise
        float v0k = 1.f;
        int i = 0;
        Bi_vecteur<int> loca = grille.localisation(x0[0], x0[1]);  // localisation du point de départ dans la grille
        while(i<=max_iter && v0k>0){  // on cherche la première occurence n de v_n telle que le point de départ soit négatif
            v0k = interpolation<float, Vecteur<float>>(loca, x0[0], x0[1], i, HJB_new.v, grille);
            i++;
        }
        n=i-1; // n est la dernière occurence où v(x0, n) est positive
        if(i>max_iter){throw logic_error("Temps trop court pour trouver une solution convenable.");} // si ce n'est jamais le cas, on a un problème
        return (*this).n;
    }

    commandes_discretes calcul(Vecteur<float>& x0, int L){
        positions.X.clear();
        positions.Y.clear();
        if(HJB_new.resolved==0){HJB_new.resolve(L);} // On résout HJB si il n'a jamais été résolu, sinon on peut procédé
        // print_grille(grille, HJB_new.v);
        Bi_vecteur<int> loca = grille.localisation(x0[0], x0[1]); // localisation du point de départ dans la grille
        float vx = interpolation<float, Vecteur<float>>(loca, x0[0], x0[1], 0, HJB_new.v, grille); // interpolation sur v du point de départ
        int iter = 0;
        n = calcul_n(x0);  //calcul du nombre d'iteration nécessaire

        positions.pushback(x0); // bi_vecteur des positions optimales du bateau
        while(vx>0 && iter<=n){ // tant que nous ne sommes pas arrivé dans la zone (ou très proche, lorsque iter=n)
            float mini = numeric_limits<float>::max();  // voir HJB.calcul
            float minimiseur;
            Vecteur<float> next_pos(2);  // prochaine position calculée
            float commande;
            Vecteur<float> opti_pos(2);  // prochaine position optimale trouvée
            bool erreur = 1;  // on postule qu'il y a une erreur de base, et si tout se passe bien on la met à 0

            for(int l=0;l<L;l++){
                Vecteur<float> vit = vitesse.f(positions[iter], float(l)/float(L)*360.f-180.f, iter);
                next_pos = positions[iter] + vit*grille.resolution; // calcul de la prochaine position à partir de la vitesse et du pas de temps
                loca = grille.localisation(next_pos[0], next_pos[1]); // prochaine localisation dans la grille
                if(loca.X[0]>=0 && loca.Y[0]>=0 && loca.X[2]<=int(grille.taille_X/grille.pas) && loca.Y[2]<=int(grille.taille_Y/grille.pas)){
                    // si la commande ne nous amène pas en dehors de la zone d'étude
                    minimiseur = interpolation<float, Vecteur<float>>(loca, next_pos[0], next_pos[1], n-iter, HJB_new.v, grille);
                    if(minimiseur<mini){
                        mini=minimiseur;
                        commande=float(l)/float(L)*360.f-180.f;
                        opti_pos = next_pos;
                        erreur = 0; //nous avons pu modifié la commande, il n'y a donc pas eu de blocage en bord de zone
                    }
                }
            }

            if(erreur){  // est-ce que nous n'avons jamais modifié la commande
                cout<<positions<<endl;
                cout<<commandes<<endl; 
                throw logic_error("Le bateau ne veut que sortir de la zone !"); // toutes les commandes nous amènent en dehors de la zone 
                // -> probleme
            }

            positions.pushback(opti_pos);
            commandes.commandes.push_back(commande);
            loca = grille.localisation(opti_pos[0], opti_pos[1]);
            vx = interpolation<float, Vecteur<float>>(loca, opti_pos[0], opti_pos[1], 0, HJB_new.v, grille); //nouvelle valeur de v en la position considéré
            // Pour rappel, on veut qu'elle soit négative, ce qui signifie qu'on est arrivé dans la zone cible
            iter++;
        }
        if(vx>0){ // Si le programme s'est arrêté sans que nous soyons en zone, il y a eu un problème d'interpolation,
            cout<<"on ne peut plus proche... ";} // mais nous sommes très proche de la zone
        return commandes;
    }
};

#endif