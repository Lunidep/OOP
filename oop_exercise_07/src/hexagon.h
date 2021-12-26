#ifndef _HEXAGON_H_
#define _HEXAGON_H_

#include "figure.h"
using namespace std;

struct hexagon : figure {
private:
    double side;
public:
    void print(ostream&) const  override ;
    void printFile(ofstream&) const override ;
    double area() const override ;
    hexagon() = default;
    hexagon(istream& is);
    hexagon(ifstream& is);
}; 

#endif
