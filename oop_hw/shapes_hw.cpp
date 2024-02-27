#include <iostream>

using namespace std;


class Point{
    public:
    int x, y;
    Point(int x, int y): x(x), y(y){}
    int getX() const {return x;}
    int getY() const {return y;}
};


class Shape{
    public:
    string shapeName = "Shape";

    void setShapeName(string name) {
        shapeName = name;
    }

    string getShapeName() {
        return shapeName;
    }

    void printShapeName() {
        cout << shapeName << endl;
    }

    virtual bool isPointInside(const Point& p);
};

bool Shape::isPointInside(const Point &p) {
    return false;
}


class Circle: public Shape{

    private:
    Point center;
    int radius;

    public:
    Circle(const Point& center, int radius): center(center), radius(radius){
        this->setShapeName("Circle");
    }

    virtual bool isPointInside(const Point& p) {
        double distance = std::sqrt(std::pow(p.getX() - center.getX(), 2) + std::pow(p.getY() - center.getY(), 2));
        return distance <= radius;
    }
};


class Square: public Shape{
    private:
    Point topLeft;
    int side;

    public:
    Square(const Point& topLeft, int side): topLeft(topLeft), side(side){
        this->setShapeName("Square");
    }

    virtual bool isPointInside(const Point& p) {
        int pointX = p.getX();
        int pointY = p.getY();

        bool conditionX = pointX >= topLeft.getX() && pointX <= topLeft.getX() + side;
        bool conditionY = pointY >= topLeft.getY() && pointY <= topLeft.getY() + side;
        return conditionX && conditionY;
    }
};


class Triangle: public Shape{
    private:
    Point a, b, c;

    public:
    Triangle(const Point& a, const Point& b, const Point& c): a(a), b(b), c(c){
        this->setShapeName("Triangle");
    }

    bool barycentricCoordinates(const Point& p, const Point& v1, const Point& v2) {
        int x = p.getX();
        int y = p.getY();

        return (x-v1.getX()) * (v2.getY()-v1.getY()) - (v2.getX()-v1.getX()) * (y-v1.getY()) > 0;
    }

    virtual bool isPointInside(const Point& p) {
        bool sign1 = barycentricCoordinates(p, a, b);
        bool sign2 = barycentricCoordinates(p, b, c);
        bool sign3 = barycentricCoordinates(p, c, a);

        return sign1 == sign2 && sign2 == sign3;
    }
};

int main(){
    Point p(0, 0);

    Shape* shapes[3] = {
        new Circle(p, 5),
        new Square(p, 5),
        new Triangle(Point(0, 0), Point(0, 5), Point(5, 0))
    };

    for (int i = 0; i < 3; i++){
        Shape* shape = shapes[i];

        shape->printShapeName();

        bool isInside = shapes[i]->isPointInside(Point(2, 2));
        string result = isInside ? "Point is inside" : "Point is outside";
        cout << result << endl;
    }
}
