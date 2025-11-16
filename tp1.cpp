#include <iostream>
#include <cstdlib>

bool is_empty(int *tab, int nb)
{
    bool b=1;
    if (nb==0)
    {
        
        //std::cout<<b<<std::endl;
        return b;
    }
    else
    {
        
        //std::cout<<!b<<std::endl;
        return !b;
    }
}

bool is_full(int *tab, int size, int nb)
{
    bool b=1;
    if (nb>=size)
    {
        
        //std::cout<<b<<std::endl;
        return b;
    }
    else
    {
        
        //std::cout<<!b<<std::endl;
        return !b;
    }
}


void push (int *tab, int size, int& nb, int a)
{
    if (is_full(tab,size,nb)==1)
    {
        std::cerr<<"LISTE PLEINE"<<std::endl;
    }
    else 
    {
    tab[nb]= a ;
    nb+=1 ;
    }
}

void print(int *tab, int size, int nb)
{
    std::cout<<"tab=[";
    int i = 0;
    while (i < nb) 
    {
        
        std::cout<<tab[i]<<" ";
        i+=1;
    }
    std::cout<<"] et size="<<size<<" et nb="<<nb <<std::endl;
}






int top(int *tab, int size, int nb)
{
    
    if (is_empty(tab,nb)==1)
    {
        
        std::cerr<<"LA PILE EST VIDE"<<std::endl;
    }
    else
    {
        
        //std::cout<<tab[nb-1]<<std::endl;
        return tab[nb-1];
    }
    return -1;
}


int pop(int *tab, int size,int &nb)
{
    
    if (is_empty(tab,nb)==1)
    {
        
        std::cerr<<"LA PILE EST VIDE"<<std::endl;
    }
    else
    {
        
        //std::cout<<tab[nb-1]<<std::endl;
        nb=nb-1;
        return tab[nb];
        
        
    }
    return -1;
}


int main()
{
    int size = 5;
    int tab[size]; // crée tableau vide de taille 5
    int nb = 0;

    print(tab, size, nb); 
    push(tab, size, nb, -17);  
    std::cout << top(tab, size, nb) << std::endl; 
    push(tab, size, nb, 90);
    print(tab, size, nb); 
    int e = pop(tab, size, nb);
    std::cout << e << std::endl;
    print(tab, size, nb); 

    push(tab, size, nb, 20);
    push(tab, size, nb, -78);
    push(tab, size, nb, -9);
    print(tab, size, nb); 
    push(tab, size, nb, -56);
    print(tab, size, nb); 
    push(tab, size, nb, -9);
    push(tab, size, nb, 68);
    
    return 0;
}
