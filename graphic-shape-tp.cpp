/* implement graphic shapes and an editor

the graphic shapes:
   - are Circle (radius), Rectangle (width, height) ...
   - have a position: x, y
   - can be moved
   - have member function that check if a shape is at a given position
     (juste check that the given point is inside the smallest rectangular bounding box englobing the shape)
   - have a member function that compute the area of the shape (fix a value for PI)

the editor:
  - contains a list of graphic shapes
  - can add/remove an existing graphic-shape to the list
  - has a member function find that returns the (first) graphic shape at a given position
  - can remove the graphic-shape found at a given position
  - can compute the area of the shape found at a given position

We can add a new shape to your code (Square) WITHOUT modifying your classes !
Only by adding some code and modifying the main function.

*/
/*
Circle c1 (12, 56, 3);
Rectangle r1 (10, 50, 34, 78);
std::vector<???> shapes;
shape.push_back(??c1);
shape.push_back(??r1);
*/
#include <iostream>
#include <cstdlib>
#include <vector>

class Shape // comme on a mis virtual, il a crée un object abstract (en gros sous catheg de d'autres colasses)
{
    int x;
    int y;

protected:
    Shape(int n = 1, int p = 1) : x(n), y(p) {}

public:
    void move(int dx, int dy)
    {
        x = x + dx;
        y = y + dy;
        return;
    }
    virtual int area()=0 ;//  jsp demander a copilot de m expliquer
    //askip elle a pas de corps

};

class Circle : public Shape
{
    int r;

public:
    Circle(int x, int y, int r) : Shape(x, y), r(r) {}
    int area()
    {
        return 3.14 * r * r;
    }
};

class Rectangle : public Shape
{
    int l;
    int h;

public:
    Rectangle(int x, int y, int r, int d) : Shape(x, y), l(r), h(d) {}
    int area()
    {
        return l * h;
    }
};

void foo(Shape& a) {std::cout<<a.area()<<std::endl;}
 

int main()
{
    Circle c1(100, 200, 300);
    c1.move(8, 10);
    std::cout << c1.area() << std::endl;

    Rectangle r1(100, 300, 56, 57);
    r1.move(8, 10);
    std::cout << r1.area() << std::endl;

    std::vector<Shape *> shapes;
    shapes.push_back(&c1);
    shapes.push_back(&r1);

    for (int i=0; i<shapes.size(); i++)
    {std::cout <<    shapes[i]->area()<<std::endl; 
        // ca va pas marcher car area n est pas def sur shape : 
        //une solution, créer une fonction void foo(       //
    shapes[i]->move(2,3);}

    /*
    Circle c2(30, 120, 45.89);

    Rectangle r1(30, 40, 60, 50);
    r1.area();

    Rectangle r2(70, 80, 100, 67);

    Editor ed;
    ed.add(c1);
    ed.add(c2);
    ed.add(r1);
    ed.add(r2);

    ed.find(71, 81).area();
    ed.find(30, 120).move(10, 80);
  */
    return 0;
}