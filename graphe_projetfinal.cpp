#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits> // Pour l'algo de Floyd Warshall


//je n'ai quasiment pas utilié d'IA, sauf pour débugger mon dfs et comprendre la syntaxe des unordered_map :)
//ca m'a pris hyper longtemps mais ça marcheee!!!!!



class Vertex; // même problème que la dernière fois sinon (ja parle d'une classe pas encore declarée)
class Edge;
class Graph;


struct Matrix // je suis obligé de le refaire pcque j ai perdu mon tp Matrix à cause des histoire de Git
{
    int r = 0;
    int c = 0;
    std::vector<int> liste;

    Matrix(int n, int p) : r(n), c(p), liste(r * c) {}

    void mprint() // faite après madjprint (cf plus bas) (même chose mais sans les m->)
    {
        int n = 0;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                std::cout << liste[n] << " ";
                n = n + 1;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};





class Edge
{
    friend Vertex;
    friend Graph;

    double val;
    Vertex *begin;
    Vertex *end;

    Edge(Vertex *a, Vertex *b, double v) : val(v), begin(a), end(b) {}
};







class Vertex
{
    friend Edge;
    friend Graph;

    std::string name;
    std::vector<Edge *> v;

    Vertex(std::string n) : name(n) {}

public:

    ~Vertex() //je crois que ca va ici car c'est vertex qui stocke les edge (je fais new plus tard)
    {
        for (int i = 0; i < v.size(); i++)
        {
            delete v[i];
        }
    }
};








class Graph
{

    std::vector<Vertex *> g;
    std::unordered_map<std::string, int> ug;
    Matrix *M = new Matrix(0, 0); 

public:
    ~Graph() // je crois que ça va ici car graph stocke les matrices et vertex
    {
        delete M;
        for (int i = 0; i < g.size(); i++)
        {
            delete g[i];
        }
    }

    void add_vertex(std::string n)
    {
        Vertex *pv = new Vertex(n);
        g.push_back(pv);
        ug[n] = g.size() - 1;
    }

    void add_edge(const std::string &begin, const std::string &end, double value)
    {
        // vérif si existent deja les sommets :

        int n = g.size();
        if (ug.find(begin) == ug.end())  //IA utilisée ici car je comprenais pas trop la syntaxe (ug.find(begin) == ug.end())
        {
            add_vertex(begin);
        }
        if (ug.find(end) == ug.end())
        {
            add_vertex(end);
        }

        // création new edge

        Edge *pe = new Edge(g[ug[begin]], g[ug[end]], value);
        (g[ug[begin]]->v).push_back(pe);
    }

    void appelrecursif(std::set<Vertex *> &vis, Vertex *start) //appel récursif de dfs 
    
    //j'ai eu qq problèmes d'homogénéité de types et je ne comprenais pas les messages du terminal: l'IA m'a aidé ici par eg :
    // J'avais des erreurs que je comprenais pas dans le terminal, l'IA m'indique que je compare des edge
    // et des vertex car je faisais (vis.find((start->v)[i]) == vis.end()), je comprends tout de suite qu il me manque un ->end qq part

    //Je ne comprenais pas pourquoi le programme affichait plusieurs fois la même ville 
    //l'IA m'indique qu'il manque le & et que je perds sinon des infos lorsque je revient d'un appel récursif. Cela est logique d'utiliser donc le & 
    //qui réfèrera toujours vers le même set et donc ne perdra pas l'information

    {
        std::cout << start->name << std::endl; 
        for (int i = 0; i < (start->v).size(); i++)
        {
            if (vis.find((start->v)[i]->end) == vis.end()) // si il a pas été visité
            {
                vis.insert((start->v)[i]->end);           // on l append à vis
                appelrecursif(vis, ((start->v)[i]->end)); // et on le visite
            }
        }
    }

    void dfs()
    {
        Vertex *start = g[0];
        std::set<Vertex *> vis;
        vis.insert(start);
        appelrecursif(vis, start);
    }

    void madj()
    {
        int n = g.size(); 
        this->M = new Matrix(n, n);  
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < g[i]->v.size(); j++)
            {
                this->M->liste[i * n + ug[g[i]->v[j]->end->name]] = g[i]->v[j]->val; //moche mais ça marche y a probablement plus efficace en terme de syntaxe
            }
        }
    }

    void madjprint() // copiée du TP Matrix avec les M-> en plus pcqu on est dans graphe
    {
        int n = 0;
        for (int i = 0; i < M->r; i++)
        {
            for (int j = 0; j < M->c; j++)
            {
                std::cout << M->liste[n] << " ";
                n = n + 1;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    Matrix AlgorithmedeFloydWarshall()
    {
        Matrix W = Matrix(this->M->r, this->M->c);

        //initialisation de W : on veut : les distances connues et infini ailleurs.
        //sauf que C++ stocke des int sur des octets donc y a un nb max avec limits
        //j'utilisais donc std::numeric_limits<int>::max() ( https://stackoverflow.com/questions/8690567/setting-an-int-to-infinity-in-c )
        //mais ca overflowait et j'avais des valeurs négatives dans ma matrice de distance donc je prends ici un max arbitraire = 1 000 000


        int INF = 1000000; 

        for (int i = 0; i < this->M->r * this->M->r; i++) // "inf" partout
        {
            W.liste[i] = INF;
        }

        for (int i = 0; i < this->M->r; i++) // diag=0
        {
            W.liste[i * this->M->r + i] = 0;
        }

        for (int i = 0; i < this->M->r; i++) //ajout des dist existentes
        {
            for (int j = 0; j < g[i]->v.size(); j++)
            {
                W.liste[i * this->M->r + ug[g[i]->v[j]->end->name]] = g[i]->v[j]->val;
            }
        }

        // je reprends bêtement le principe du pseudo code sur Wikipedia

        for (int k = 0; k < this->M->r; k++)
        {
            for (int i = 0; i < this->M->r; i++)
            {
                for (int j = 0; j < this->M->r; j++)
                {
                    int min = 0;
                    if (W.liste[i * (this->M->r) + j] < W.liste[i * (this->M->r) + k] + W.liste[k * (this->M->r) + j])
                    {
                        min = W.liste[i * (this->M->r) + j];
                    }
                    else
                    {
                        min = W.liste[i * (this->M->r) + k] + W.liste[k * (this->M->r) + j];
                    }
                    W.liste[i * (this->M->r) + j] = min;
                }
            }
        }
        return W;
    }
};

Graph read_triplet(const std::string &filename) // ON ME DIT DE CODER LA FONCTION MAIS ELLE EST DEJA CODEE DANS LE SUJET 
{
    Graph g;
    std::cout << "read_triplet(" << filename << ")" << std::endl;
    std::ifstream file(filename);
    if (not file.is_open())
    {
        throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
    }
    std::string from, to;
    double value;
    while (file >> from >> to >> value)
    {
        std::cout << from << " " << to << " " << value << std::endl;
        g.add_edge(from, to, value);
    }
    std::cout << std::endl;
    file.close();
    return g;
}

int main()
{

    Graph graph = read_triplet("graph0.txt");
    graph.dfs();
    graph.madj();
    graph.madjprint();
    graph.AlgorithmedeFloydWarshall().mprint();

    return 0;
}
