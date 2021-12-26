#ifndef Hexagon_H
#define	Hexagon_H
#include <cstdlib>
#include <iostream>
//#include "Figure.h"
using namespace std;

class Hexagon{// : public Figure {
public:
	Hexagon();
	Hexagon(istream& is);
	Hexagon(const Hexagon& orig);
	Hexagon(long int i);

	friend bool operator==(const Hexagon& left, const Hexagon& right);
	friend bool operator<(Hexagon& left, Hexagon& right);

	friend ostream& operator<<(ostream& os, const Hexagon& obj);
	friend istream& operator>>(istream& is, Hexagon& obj);

	Hexagon& operator=(const Hexagon& right);

	long double area();
	void Print();
	~Hexagon();
private:
	long int side;
};

#endif