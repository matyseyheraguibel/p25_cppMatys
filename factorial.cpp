#include <iostream>
#include <cstdlib>




int main(int argc, char *argv[])
{

    int i = 1; 
    int fact = 1;
    while (i < std::atoi(argv[1])+1)

    {
        fact = fact * (i);
        i = i + 1;
    }

    std::cout << "le réstultat est " << fact << std::endl;
    

}
