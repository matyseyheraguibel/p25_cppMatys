/*
Nous souhaitons implémenter un arbre binaire.

Un arbre binaire est formé de noeuds (Node).

Chaque noeud a deux sous-arbres (left, right) potentiellement nuls et une valeur entière.

Un de ces noeuds est la racine de l'arbre, tous les noeuds de l'arbre sont accessibles à partir de cette racine.

Voici un exemple d'arbre avec 3 noeuds,
on le dessine "allongé" avec sa racine à gauche:

      37
26
      11

   la racine est 26
   l'arbre gauche est réduit au noeud 11
   l'arbre droit est réduit au noeud 37

Un autre avec les mêmes valeurs
mais une autre forme (la forme dépend de l'ordre d'insertion des éléments)
            37
      26
11

Vous l'avez compris, étant donné un noeud:
   - les valeurs des noeuds du sous-arbre gauche sont strictement inférieures à la valeur du noeud
   - les valeurs des noeuds du sous-arbre droit sont strictement supérieures à la valeur du noeud.

Voici le dessin de l'arbre nous allons prendre en exemple dans le main (8 est la racine):
en trichant on a inséré les valeurs de manière à ce qu'il soit équilibré...
Quel est la complexité en temps de la recherche d'un élément dans un arbre binaire équilibré ?
dégénéré
               15
          14
               13
     12
               11
          10
               9
8
               7
          6
               5
     4
               3
          2
               1

Si j'ai beaucoup moins de chance, je peux obtenir en insérant les mêmes valeurs
un arbre "dégénéré":
30
     29
          28
               27
                    26
                         25
                              24
                                   23
                                        22
                                             21
                                                  20
                                                       19
                                                            18
                                                                 17
                                                                      16

Quel est la complexité en temps de la recherche d'un élément dans des arbres binaires de cette forme ?

O(n) si dégénéré
ln(n) sinon

I) Construction de l'arbre:

L'arbre est construit de manière à être trié c'est à dire quand on est à un noeud:
   - toutes les valeurs de son sous-arbre gauche sont strictement inférieures à la valeur du noeud
   - toutes les valeurs de son sous-arbre droit sont strictement supérieures à la valeur du noeud

On donne des indices mais vous pouvez coder autrement.

L'arbre initial est créé vide - sa racine est donc le pointeur nul (nullptr).

Implémenter la méthode insert(int v) qui ajoute une valeur entière à l'arbre à la bonne place i.e.
  - on va se déplacer dans l'arbre jusqu'à trouver l'endroit où insérer cette valeur
  - si la valeur existe déjà dans l'arbre, on ne fait rien
  - sinon on crée un noeud qu'on raccorde.

  Réfléchissez à la manière de faire un tel parcours récursivement, soit codez-le soit regardez les indices ci-dessous.

Indices pour l'insertion dans l'arbre binaire:
  - si la racine n'existe pas on crée un noeud avec la valeur et ses deux sous-arbres nuls (nullptr)
  - si la racine existe on lance l'insertion sur ce noeud racine (on appelle une méthode d'insertion des noeuds)

Indices pour la méthode d'insertion sur un noeud:
  - si la valeur du noeud est égale à la valeur à insérer on ne fait rien (le noeud y est déjà)
  - si la valeur est inférieure et si l'arbre gauche existe on lance l'insertion sur le noeud gauche
  -                             et si l'arbre gauche n'existe pas, on crée un noeud avec la valeur et il devient le fils gauche
  - pareil à droite

II) Parcours de l'arbre:

Implémentez la méthode depth() qui va parcourir cet arbre en profondeur en affichant ses valeurs.
Réfléchissez à la manière de faire ce parcours de manière récursive et soit vous le codez soit vous lisez les indices ci-dessous.

Indices pour un parcours en profondeur récursif d'un arbre binaire:
   - ce parcours lance le parcours récursif du noeud racine de l'arbre (i.e. appelle la méthode depth des noeuds)
   - si ce noeud a un fils gauche, on lance le parcours sur le noeud gauche (i.e. appelle la méthode sur le noeud gauche)
   - si ce noeud n'a pas de fils gauche, on affiche la valeur du noeud et on lance le parcours sur le noeud droit
...

Lors de ce parcours on peut afficher la valeur des noeuds à plusieurs endroits:
   - si on l'affiche en début de l'appel du parcours sur un noeud: on a un affichage dit préfixe
   - si on l'affiche entre les appels à gauche et à droite on a un affichage dit infixe
   - si on l'affiche à la fin de l'appel de la méthode sur un noeud: on a un affichage dit postfixe

Pour décider de l'affichage, on peut donc passer à cette méthode le type de l'affichage désiré
(par exemple un objet qui est une énumération (enum) voir exemple ci-dessous)

*/
#include <iostream>

// the type enum
enum Order
{
     Prefix,  // will be set to 0
     Infix,   // will be set to the previous + 1
     Postfix, // idem
};

void enum_values()
{
     std::cout << "Prefix is " << Order::Prefix << std::endl;
     std::cout << "Infix is " << Order::Infix << std::endl;
     std::cout << "Postfix is " << Order::Postfix << std::endl;
}

// Les structures de base de l'arbre binaire BinaryTree et Node:
// avec les méthodes pour que le code compile.
struct Node
{
     int val;
     Node *left;
     Node *right;
     Node(int val, Node *left = nullptr, Node *right = nullptr) : val(val), left(left), right(right) {}
};

struct BinaryTree
{
     Node *root = nullptr;
     // BinaryTree() : root(nullptr) {}

     void insert(int j)
     {
          if (root == nullptr)
          {
               root = new Node(j);
               return;
          }

          Node *act = root;

          while (true)
          {
               if (j < act->val)
               {
                    if (act->left == nullptr)
                    {
                         act->left = new Node(j);
                         return;
                    }
                    act = act->left;
               }
               else if (j > act->val)
               {
                    if (act->right == nullptr)
                    {
                         act->right = new Node(j);
                         return;
                    }
                    act = act->right;
               }
               else
               {
                    return;
               }
          }
     }


     bool search(int v)
          {
               Node *o = this->root;
               bool b1 = search1(o,v);
               return b1 ;
          }

     bool search1(Node *o, int v)
     {
          if (o->val == v)
          {
               return 1;
          }
          else
          {
               if (o->val > v)
               {
                    if (o->left != nullptr)
                    {
                         return search1(o->left,v) ;
                    }
                    else
                    {
                         return 0;
                    }
               }
               else
               {
                    if (o->right != nullptr)
                    {
                         return search1(o->right,v) ;
                    }
                    else
                    {
                         return 0;
                    }
               }
          }
     }

     // celle là est plus difficile

     void print() {}
     //ok ca fait 15 minutes que je réflechis que j'essaye des trucs et j'ai aucune idee
     
};

inline void depth(Node *o) // QUESTION LE INLINE COMMENT IL SAIT C'EST POUR QUELLE CLASSE? (node ou tree)?. 2eme question : ca change rien de la mettre la et, pk pas la mettre directement dans la struct/classe (elle serait pas inline si c'était le cas?)
{
     std::cout << o->val << '\n';
     if (o->left != nullptr)
     {
          depth(o->left);
     }
     if (o->right != nullptr)
     {
          depth(o->right);
     }
}

int main()
{
     enum_values(); // exemple pour voir un enum

     BinaryTree b;
     b.insert(8);
     b.insert(4);
     b.insert(6);
     b.insert(12);
     b.insert(10);
     b.insert(11);
     b.insert(9);
     b.insert(2);
     b.insert(1);
     b.insert(3);
     b.insert(5);
     b.insert(14);
     b.insert(15);
     b.insert(13);
     b.insert(7);
     depth(b.root);
     bool B3=b.search((5)) ;
     std::cout << B3 << '\n' ;
     bool B4 =b.search(19) ;
     std::cout << B4 << '\n' ; ///YYEEESSS CA MARCHHEE
     //b.print() ;









     return 0;
}

/* l'exécution de ce programme donne:
    ----------------------------------

Prefix is 0
Infix is 4
Postfix is 5
               15
          14
               13
     12
               11
          10
               9
8
               7
          6
               5
     4
               3
          2
               1
Infix { 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15  }
Postfix { 1 3 2 5 7 6 4 9 11 10 13 15 14 12 8  }
Prefix { 8 4 2 1 3 6 5 7 12 10 9 11 14 13 15  }
false
true
Cet arbre est dégénéré:
                                                                      15
                                                                 14
                                                            13
                                                       12
                                                  11
                                             10
                                        9
                                   8
                              7
                         6
                    5
               4
          3
     2
1

celui là aussi:
30
     29
          28
               27
                    26
                         25
                              24
                                   23
                                        22
                                             21
                                                  20
                                                       19
                                                            18
                                                                 17
                                                                      16
*/
