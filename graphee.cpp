#include <iostream>
#include <cstdlib>
#include <vector>

struct Edge;

struct Vertex
{
    int name;
    std::vector<Edge *> v;
    Vertex(int n) : name(n) {}
    void print(); // je la decl mais la def pas pcque sinon il connait pas encore print de edge
};

struct Edge
{
    double val;
    Vertex *begin;
    Vertex *end;

    Edge(Vertex *a, Vertex *b, double v) : val(v), begin(a), end(b) {}

    void print()
    {
        std::cout << "begin = " << begin->name << " and end =" << end->name << " and val =" << val << std::endl;
        return;
    }
};

void inline Vertex::print() //la je peux def car c apres Edge dcp il connait kle print de edge
{
    for (int m=0; m < v.size(); m++)
    {
        v[m]->print();
    }
    return;
}

struct Graph
{
    std::vector<Vertex *> g;

    void addvertex(int n)
    {
        Vertex *pv = new Vertex(n);
        g.push_back(pv);
    }

    void addEdge(int n, int p, double k)
    {
        int max;
        if (n >= p)
        {
            max = n;
        }
        else
        {
            max = p;
        }
        for (int i = g.size(); i <= max; i++) // création de vertex
        {
            addvertex(i);
        }
        // création de edge
        Edge *pe = new Edge(g[n], g[p], k);
        (g[n]->v).push_back(pe);
    }

    void print()
    {
        for (int i=0; i < g.size(); i++)
        // for (int j; j<(g[i]->v).size() ;j++) CA MARCHEEPAAASSS
        {
            g[i]->print();
        }
    }
};

//j ai pas fait les destructeurs et j ai des seg fault MAIS CA MARCHE!!!!!!!!

int main()
{
    Graph gr;
    gr.addEdge(1, 2, 526.1);
    gr.addEdge(1, 3, 92);
    gr.print();
    (gr.g[0]->v[0])->print();
    return 0;
}
