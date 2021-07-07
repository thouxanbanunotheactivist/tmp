#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <sstream>
#include <math.h>
using namespace std;

class Figure{
public:
    virtual string Name () const = 0;
    virtual double Perimeter () const = 0;
    virtual double Area () const = 0;
};
class Circle : public Figure {
public:
    Circle(const double& r) : _r (r){}
    string Name() const override {
        return "CIRCLE";
    }
    double Perimeter() const override{
        return (_r * 6.28);
    }
    double Area() const override{
        return (_r*_r*3.14);
    }
private:
    const double _r;
};
class Rect : public Figure{
public:
    Rect (const double& x, const double& y) : _x(x), _y(y){}
    string Name() const override{
        return "RECT";
    }
    double Perimeter() const override{
        return ((_x+_y)*2);
    }
    double Area() const override{
        return (_x*_y);
    }
private:
    const double _x,_y;
};
class Triangle : public Figure{
public :
    Triangle (const double& x, const double& y, const double& z) : _x(x), _y(y), _z(z){}
    string Name() const override{
        return "TRIANGLE";
    }
    double Perimeter() const override{
        return (_x+_y+_z);
    }
    double Area() const override{
        double pp = (_x+_y+_z)/2;
        return (sqrt(pp*(pp-_x)*(pp-_y)*(pp-_z)));
    }
private:
    const double _x,_y,_z;
};

shared_ptr<Figure> CreateFigure(istringstream& is){
    string type;
    is>>type;
    if(type == "CIRCLE"){
        double r;
        is>>r;
        return make_shared<Circle>(r);
    }
    else if(type == "RECT"){
        double x,y;
        is>>x>>y;
        return make_shared<Rect>(x,y);
    }
    else if(type == "TRIANGLE"){
        double x,y,z;
        is>>x>>y>>z;
        return make_shared<Triangle>(x,y,z);
    }
}

int main() {
  vector<shared_ptr<Figure> > figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);
    string command;
    is >> command;
    if (command == "ADD") {
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
