// Nous voulons implémenter un type de donné qui a la structure de liste chaînée
// et qui stocke, par exemple, des entiers.

// Une liste est composée de cellules reliées entre elles.

// Dans une liste simplement chaînée:
//   - chaque cellule pointe vers sa cellule suivante
//   - la dernière cellule n'a pas de cellule suivante

// Par exemple, la liste chaînée suivante contient les entiers 42, 12 et 45.
// 42 -> 12 -> 45 -> null

// Une cellule contient donc deux choses: une valeur et un pointeur vers sa cellule suivante
//   qui est l'adresse mémoire de la cellule suivante.

// Une liste pointe vers sa première cellule (la tête de liste) ou vers null si la liste est vide.

// Donc vous avez besoin de deux structures...

// La liste est une structure de données qui a beaucoup de défauts
// mais qui est un cas d'école sympa à implémenter en c++ et sans IA générative bien sûr -


// Il existe d'autres types de listes chaînées.
// La liste doublement chaînées où:
//    - chaque cellule pointe vers sa cellule précédente et vers sa cellule suivante
//    - la première (resp. dernière) cellule n'a pas de cellule précédente (resp. suivante)

// La liste circulaire où:
//    - chaque cellule pointe vers sa cellule suivante
//    - la dernière cellule pointe vers la première cellule 

// Ces deux dernières listes sont plus complexes à implémenter, implémentez une liste simplement chaînée
// avec les opérations de base:
//   - ajouter un élément en tête de liste  (push_front - une opération en temps constant O(1))
//   - chercher un élément dans la liste    (find -       une opération en temps linéaire O(n))
//   - supprimer un élément dans la liste   (remove -     une opération en temps linéaire O(n))
//   - afficher la liste                    (print -      une opération en temps linéaire O(n))
//   - vérifier si la liste est vide        (is_empty -   une opération en temps constant O(1))
// Non, nous ne voulons pas ajouter un élément en fin de liste:
//   - parce que nous ne voulons pas faire une opération d'ajout qui soit en temps linéaire O(n) - horrible !
// Et si on voulait une liste où on peut ajouter en tête et en fin de liste ?
//    On ferait une liste doublement chaînée avec un pointeur vers la première cellule et un vers la dernière cellule.

// Surtout dessinez la structure sur papier avant de coder
// et dessinez pas à pas des exemples d'ajout, de recherche, de suppression

// Oui il y aura un new (quelque part) et vous n'oublierez pas de libérer la mémoire
// (i.e. libérer les cellules quand elles ne sont plus utilisées)

// Voici un exemple de main qui doit fonctionner avec votre liste chaînée:

struct Cell {
int val;
Cell *as; //as pour adresse suivant
Cell (int v=0) : val(v), as(nullptr) {}
};

struct LinkedList {
  Cell *cell0;
  LinkedList():cell0(nullptr) {}

  void is_empty() {
  return cell0==nullptr ;
  }

  void push_front(int a) {
    Cell *nouv = new Cell(a) ;
    nouv->as =cell0;
    cell0=nouv ;
  }

  void print() {
    

  }

};

int main () {
    LinkedList list;

    list.push_front(45);
    list.push_front(12);
    

    return 0;
}