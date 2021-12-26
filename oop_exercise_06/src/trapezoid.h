#ifndef Trapezoid_H
#define Trapezoid_H 1

#include <utility>
#include <iostream>

template<typename T>
class Trapezoid {
	
public:
	T a, b, h;
	Trapezoid() : a(0), b(0), h(0) {}
	Trapezoid(T _a, T _b, T _h) : a(_a), b(_b), h(_h) {}
};

template<typename T>
double Area(const Trapezoid<T>& t) {
	return (t.a + t.b) * (t.h / 2);
}

template<typename T>
std::ostream& Print(std::ostream& os, const Trapezoid<T>& t) {
	os << "[a = " << t.a << " ";
	os << "b = " << t.b << " ";
	os << "h = " << t.h << " ";

	os << "Area =  " << Area(t) << "]";

	return os;
}

template<typename T>
std::istream& Read(std::istream& is, Trapezoid<T>& t) {
	std::cout << "\na = "; is >> t.a;
	std::cout << "\nb = "; is >> t.b;
	std::cout << "\nh = "; is >> t.h;

	return is;
}

template<typename T>
std::istream& operator>>(std::istream& is, Trapezoid<T>& t) {
	return Read(is, t);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& t) {
	return Print(os, t);
}

#endif