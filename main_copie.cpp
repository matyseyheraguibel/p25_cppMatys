#include <iostream>
#include <limits>


int main(int argc, char *argv[])
{

    int i = 0;
    for (int i=;i<argc ; i++)
    {
    std::cout << argv[i] << std::endl;
    
    }


ou

    while (i <= argc)
    {
        std::cout << argv[i] << std::endl;
        i = i + 1;
    }

    return 0;
}

;