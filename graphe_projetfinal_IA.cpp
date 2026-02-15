
// Je marquerais par 5 / (/////) les endroits du code que je ne comprends pas ou où l'IA a fait difféement pour les distinguer des commentaires que l'IA a générée



///// Globalement sa logique est bien plus concise que la mienne, il utilise une structure différente pour graph et edge et demande des arguments différents
///// pour ses fonctions. Il utilise cependant qq méthodes qui ne sont pas dans le cours.

///// la logique reste similaire dans certains cas même s'il arrive à être bien plus concis et clair dans sa syntaxe

/////il. fait également bcp d'excetions qui n'étaient pas forcément exigées par les questions




#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <set>
#include <limits>
#include <iomanip>

// Pré-déclaration pour les amitiés (friend)
class Graph;

// ==========================================
// Classe Edge
// ==========================================
class Edge {
    // Consigne 0: Pas d'attributs publics, pas de getters/setters.
    friend class Vertex;    
    friend class Graph;

private:
    int to_vertex_index; // Indice du sommet de destination dans le vecteur du Graphe
    double weight; /////IL N UTILISE PAS EDGE DE LA MÊME MANIÈRE QUE NOUS L'AVIONS FAIT EN CLASSE

    // Constructeur privé (accessible seulement par les friends)
    Edge(int to, double w) : to_vertex_index(to), weight(w) {}
};

// ==========================================
// Classe Vertex
// ==========================================
class Vertex {
    friend class Graph;

private:
    std::string name;
    // Consigne 2 & 3: Vecteur d'arêtes utilisant des pointeurs (new/delete)
    std::vector<Edge*> edges; 

    // Constructeur privé
    Vertex(std::string n) : name(n) {}

    // Destructeur pour nettoyer les arêtes allouées avec new
    ~Vertex() {
        for (Edge* e : edges) {
            delete e;
        }
        edges.clear();
    }
};

// ==========================================
// Classe Graph
// ==========================================
class Matrix; // Si tu as une classe Matrix externe, sinon on utilise vector<vector> ici pour simplifier

class Graph {
private:
    // Consigne 2: Vecteur de sommets (pointeurs pour new/delete)
    std::vector<Vertex*> vertices;
    
    // Consigne 2a: Correspondance nom -> indice
    std::unordered_map<std::string, int> name_to_id;

    // Consigne 6: Matrice d'adjacence stockée comme attribut
    std::vector<std::vector<double>> adjMatrix;

    // Helper pour trouver ou créer un index de sommet
    int get_or_create_index(const std::string& name) {
        if (name_to_id.find(name) == name_to_id.end()) {
            // Création nouveau sommet (Consigne 3: new)
            Vertex* v = new Vertex(name);
            int new_index = static_cast<int>(vertices.size()); 
            
            ///// JE NE COMPRENDS PAS STATIC CAST : Réponse IA : La méthode .size() 
            /////d'un std::vector ne renvoie pas un int, mais un type appelé size_t. size_t est un entier non-signé (toujours positif) et souvent
            /////plus grand (64 bits sur les systèmes modernes). int est un entier signé (peut être négatif) et souvent plus petit (32 bits).
            /////Si tu écris simplement int n = vertices.size();, le compilateur peut afficher un warning (avertissement) du type : "conversion 
            /////de size_t vers int, perte de données possible". Le static_cast dit au compilateur : "Je sais ce que je fais, convertis 
            /////explicitement cette valeur en entier."
            
            vertices.push_back(v);
            name_to_id[name] = new_index;
            return new_index;
        }
        return name_to_id[name];
    }

    // Helper récursif pour le DFS ////// OK IL LE MET EN PRIVE PAS BETE
    void dfs_recursive(int u_idx, std::set<std::string>& visited) { 
        Vertex* u = vertices[u_idx];
        
        // Marquer comme visité (on stocke le nom comme demandé implicitement, ou l'index)
        // La consigne dit "stocker les sommets déjà visités", le set stockera les noms ici pour l'affichage
        visited.insert(u->name);
        std::cout << u->name << " ";

        for (Edge* e : u->edges) {
            Vertex* v = vertices[e->to_vertex_index];
            if (visited.find(v->name) == visited.end()) {
                dfs_recursive(e->to_vertex_index, visited);
            }
        }
    }

public:
    Graph() {}

    // Destructeur (Consigne 3: delete)
    ~Graph() {
        for (Vertex* v : vertices) {
            delete v; // Le destructeur de Vertex s'occupera des Edges
        }
        vertices.clear(); /////Ok si j'ai bien compris, après avoir delete tous les vertex, il delete les adresses elle mêmes, il clear le "conteneur"
    }

    // Consigne 4: Lecture fichier.  /////à peu près la même chose que ce qui se passe chez nous
    void read_graph(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Erreur: Impossible d'ouvrir " << filename << std::endl;
            return;
        }

        std::string from_name, to_name;
        double value;

        // Lecture des triplets: from to value
        while (file >> from_name >> to_name >> value) {
            int from_idx = get_or_create_index(from_name);
            int to_idx = get_or_create_index(to_name);

            // Création de l'arête (Consigne 3: new)
            Edge* new_edge = new Edge(to_idx, value);
            vertices[from_idx]->edges.push_back(new_edge);
        }
        file.close();
    }

    // Consigne 5: Parcours en profondeur (DFS)
    void depth_first_search() {
        if (vertices.empty()) return; 

        std::set<std::string> visited;
        std::cout << "Parcours DFS (depuis le premier sommet): ";
        
        // On lance le DFS depuis le premier sommet ajouté (souvent la racine logique)
        // Pour un parcours complet d'un graphe déconnecté, il faudrait boucler sur tous les sommets.
        // Ici on suppose un départ simple.
        dfs_recursive(0, visited);
        std::cout << std::endl;
    }

    // Consigne 6: Construction Matrice d'Adjacence
    void build_adjacency_matrix() {
        int n = vertices.size();
        double inf = std::numeric_limits<double>::infinity(); ///il met infini dans la matrice d'adjacence alors que je mets des 0 quand c'est pas accessible mais le principe reste le même

        // Init: Infini partout, 0 sur la diagonale
        adjMatrix.assign(n, std::vector<double>(n, inf)); /////1. Elle dimensionne les lignes 2. Elle crée et initialise chaque ligne 3. Elle propage la valeur (Le "Assign")
        for (int i = 0; i < n; ++i) {
            adjMatrix[i][i] = 0;
        }

        // Remplissage avec les arêtes existantes
        for (int i = 0; i < n; ++i) {
            for (Edge* e : vertices[i]->edges) {
                adjMatrix[i][e->to_vertex_index] = e->weight;
            }
        }
    }

    // Consigne 7: Floyd-Warshall
    void floyd_warshall() {
        if (adjMatrix.empty()) build_adjacency_matrix();

        int n = vertices.size();
        // On travaille sur une copie ou directement sur l'attribut. 
        // L'algo modifie la matrice pour qu'elle contienne les plus courts chemins.
        // Ici on modifie adjMatrix directement.
        
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (adjMatrix[i][k] != std::numeric_limits<double>::infinity() &&
                        adjMatrix[k][j] != std::numeric_limits<double>::infinity()) {
                        
                        if (adjMatrix[i][j] > adjMatrix[i][k] + adjMatrix[k][j]) {
                            adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];
                        }
                    }
                }
            }
        }
    }

    // Méthode utilitaire pour afficher la matrice (pour vérifier Floyd-Warshall) /////Pas nécessaire 
    void print_matrix() {
        int n = vertices.size();
        std::cout << "\nMatrice des plus courts chemins (Floyd-Warshall) :\n";
        
        // En-têtes colonnes
        std::cout << std::setw(10) << " ";
        for(Vertex* v : vertices) std::cout << std::setw(10) << v->name;
        std::cout << "\n";

        for (int i = 0; i < n; ++i) {
            std::cout << std::setw(10) << vertices[i]->name; // En-tête ligne
            for (int j = 0; j < n; ++j) {
                double val = adjMatrix[i][j];
                if (val == std::numeric_limits<double>::infinity()) {
                    std::cout << std::setw(10) << "INF";
                } else {
                    std::cout << std::setw(10) << val;
                }
            }
            std::cout << "\n";
        }
    }
};

// ==========================================
// Main (Test)
// ==========================================
int main() {
    // Création d'un fichier graphe temporaire pour le test
    {
        std::ofstream temp("graph_IA_test.gr");
        temp << "A B 5.0\n";
        temp << "B C 3.0\n";
        temp << "A C 10.0\n";
        temp << "C D 1.0\n";
        temp << "D A 2.0\n"; // Cycle pour tester
        temp.close();
    }

    Graph g;
    
    std::cout << "--- Lecture du graphe ---\n";
    g.read_graph("graph_IA_test.gr");

    std::cout << "\n--- Test DFS ---\n";
    g.depth_first_search();

    std::cout << "\n--- Construction Matrice et Floyd-Warshall ---\n";
    g.build_adjacency_matrix();
    g.floyd_warshall();
    g.print_matrix();

    return 0;
}