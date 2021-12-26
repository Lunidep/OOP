#ifndef _PENTAGON_H_
#define _PENTAGON_H_
 
#include "figure.h"
using namespace std;

struct pentagon : figure{
private:
    double side;
public:
    void print(ostream&) const override ;
    void printFile(ofstream&) const override ;
    double area() const override ;
    pentagon() = default;
    pentagon(istream& is);
    pentagon(ifstream& is);
};
 
#endif
