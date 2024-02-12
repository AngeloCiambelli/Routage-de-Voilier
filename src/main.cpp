#include <iostream>
#include "routage_voilier.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello world!" << std::endl;

    //test vecteur
    cout << vecteur({1,2,3}) << endl;
    
   //test
    //Test bi_vecteur
    vecteur<int> A({1,2,3});
    vecteur<int> B({1,2,3});
    cout << A;
    bi_vecteur<int> champs(A,B);
    cout << champs << endl;
    champs.pushback(pair(8,9));
    cout << champs;
}

