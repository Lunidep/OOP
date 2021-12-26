#ifndef _OCTAGON_H_
#define _OCTAGON_H_
 
#include "figure.h"
using namespace std;

struct octagon : figure {
private:
    double side;
public:
    void print(ostream&) const override;
    void printFile(ofstream&) const override;
    double area() const override;
    octagon() = default;
    octagon(istream& is);
    octagon(ifstream& is);
};

#endif
 