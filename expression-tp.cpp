/*

implement a hierarchy of classes for arithmetic expression manipulations:
    - the classes holds, evaluates and prints arithmetic expressions
    - print in infix, prefix or postfix notation

Additional work:
   - note that the postfix notation is also called Reverse Polish notation (RPN)
   - it is a mathematical notation in which operators follow their operands
   - this notation does not need any parentheses i.e. this notation is non ambigu
   - => you can read (easily) RPN expressions using a stacks
  implement a code to read RPN expression and store them with your class objects
  RPN arithmetic expression are passed as main command-line arguments

./main 87 12 - + 75 -
*/
#include <iostream>
#include <cstdlib>

class Expression
{
    public: 
    virtual ~Expression() {} 
    virtual void print() const {}; 
    virtual int eval() const {return 0;};
};



class Constant : public Expression
{

    int d;
    
public: 
    Constant(int p) : d(p) {}
    void print() const
    {
        std::cout<<d;
        return;
    }
    int eval() const { return d; }
};

class UnaryMinus : public Expression
{
    Expression *e;
    
public: 
UnaryMinus(Expression *o) : e(o){}
    void print() const
    {
        std::cout<<e->eval()<<"-";
        return;
    }
    int eval() const  { return -e->eval(); }
};

class Plus : public Expression
{
    Expression *g;
    Expression *d ;
   
public:
 Plus(Expression*a,Expression*b) :g(a), d(b) {}
    void print() const
    {
        std::cout<<g->eval()<<"+"<<d->eval();
        return;
    }
    int eval() const  { return g->eval()+d->eval(); }
};

class Minus : public Expression
{
    Expression *g;
    Expression *d ;
    
public:
Minus(Expression*a,Expression*b) :g(a), d(b) {}
    void print() const
    {
        std::cout<<g->eval()<<"-"<<d->eval();
        return;
    }
    int eval() const  { return g->eval()-d->eval(); }
};


class Divide : public Expression
{
    Expression *g;
    Expression *d ;
    
public: 
Divide (Expression*a,Expression*b) :g(a), d(b) {}
    void print() const
    {
        std::cout<<g->eval()<<"/"<<d->eval();
        return;
    }
    int eval() const  { return g->eval()/d->eval(); }
};

int main()
{
    try
    {
        // Constant c1(12), c2(-87), c3(23); // try it (-87 is not an unsigned int)
        Constant c1(12), c2(87), c3(75);

        c1.print(); // affiche 12
        std::cout << std::endl;
        std::cout << "eval " << c1.eval() << std::endl; // affiche 12

        UnaryMinus u1(&c1);
        u1.print(); // affiche 12 -
        std::cout << std::endl;
        std::cout << "eval " << u1.eval() << std::endl; // affiche -12

        Plus p1(&c2, &u1);
        p1.print(); // affiche 87 12 -+
        std::cout << std::endl;
        std::cout << "eval " << p1.eval() << std::endl; // affiche 75

        Minus m1(&p1, &c3);
        m1.print(); // 87 12 -+75 -
        std::cout << std::endl;
        std::cout << "eval " << m1.eval() << std::endl; // affiche 0

        Divide d1(&p1, &m1);
        std::cout << std::endl;
        std::cout << d1.eval() << std::endl; // throws an instance of 'std::runtime_error'

        std::vector<Expression*> expr;
        expr.push_back(&c1);
        expr.push_back(&u1);
        for (int i=0;i<3;i++) {
            expr[i]->print(); // On utilise -> car c'est un pointeur
            std::cout << "Res: " << expr[i]->eval()<< std::endl;
        }
    }
    catch (std::runtime_error &e)
    {
        // affiche zero divide error
        std::cout << e.what() << std::endl;
    }
    return 0;
}
