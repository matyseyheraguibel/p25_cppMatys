#include <iostream>
#include <cstdlib>

class intstack
{
private:
    int nb;
    int size;
    int *tab;

public:
    intstack(int s) : nb(0), size(s)
    {
        if (s <= 0)
            throw std::runtime_error("erreur");
        tab = new int[size];
    }

    intstack(const intstack &ss) : nb(ss.nb), size(ss.size)
    {
        tab = new int[size];
        for (int i = 0; i < nb; ++i)
            tab[i] = ss.tab[i];
    }

    intstack &operator=(const intstack &rt)
    {
        if (this != &rt)
        {
            delete[] tab;
            size = rt.size;
            nb = rt.nb;
            tab = new int[size];
            for (int i = 0; i < nb; ++i)
                tab[i] = rt.tab[i];
        }
        return *this;
    }

    ~intstack()
    {
        delete[] tab;
    }

    bool is_full()
    {
        return nb >= size;
    }

    void push(int v)
    {
        if (is_full())
            throw std::runtime_error("pile pleine");
        tab[nb++] = v;
    }

    void print()
    {
        for (int i = 0; i < nb; ++i)
        {
            std::cout << tab[i];
        }
    }

    int pop()
    {
        if (nb == 0)
            throw std::runtime_error("pile vide");
        nb = nb - 1;
        return tab[nb];
    }
};

int main()
{
        intstack s1(5);

        s1.push(10);
        s1.push(20);
        s1.push(30);
        s1.print();

        intstack s2 = s1;
        std::cout << " s2 " << s2.pop() << "\n";

        intstack s3(10);
        s3.push(111);
        s3.push(222);
        s3 = s1;
        std::cout << "s3 " << s3.pop() << "\n";

        intstack s4(2);
        s4.push(1);
        s4.push(2);
        std::cout << s4.is_full() << "\n";
        return 0;
    }
