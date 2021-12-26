#include "Hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon() : Hexagon(0) {
}

Hexagon::Hexagon(istream& is) {
	cout << "Side =";
	is >> side;
}

Hexagon::Hexagon(long int i) : side(i) {}

Hexagon::Hexagon(const Hexagon& orig) { side = orig.side; }

Hexagon::~Hexagon() {}

long double Hexagon::area() {
	long double res = 2 * sqrt(3) * pow(side, 2);
	return res;
}

Hexagon& Hexagon::operator=(const Hexagon& right) {
	if (this == &right) return *this;
	side = right.side;

	return *this;
}

bool operator<(Hexagon& left, Hexagon& right) {
	return left.area() < right.area();
}

bool operator==(const Hexagon& left, const Hexagon& right) {
	return left.side == right.side;
}

void Hexagon::Print() {
	cout << "a=" << side << endl;
	cout << "   area=" << this->area() << endl << endl;
}

ostream& operator<<(ostream& os, const Hexagon& obj) {
	os << "a=" << obj.side;
	return os;
}

istream& operator>>(istream& is, Hexagon& obj) {
	is >> obj.side;
	return is;
}