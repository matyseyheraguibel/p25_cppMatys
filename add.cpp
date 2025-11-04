#include <iostream>
#include <cstdlib>




int main(int argc, char *argv[])
{

    int i = 1; // car sinon je prend ./add
    int somme = 0;
    while (i < argc)

    {
        somme = somme + std::atoi(argv[i]);
        i = i + 1;
    }

    
    if (argc==1) {
    std::cerr << "not enough arguments"<< std::endl;
    }
    else {
    std::cout << "le réstultat est " << somme << std::endl;
    }

}

// Tout fonctionne comme dans l'énnoncé
// Si on ajoute une chaine de caractères à la ligne d'execution ./add ...  , il n'ajoute que les entiers

