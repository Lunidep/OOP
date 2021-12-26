/*
Попов Илья М80-206Б-20
Лабораторная работа №1
Вариант 10.

Это второй вариант лабораторной работы с перегрузкой операторов

Создать класс Angle для работы с углами на плоскости, задаваемыми величиной в градусах и минутах.
Обязательно должны быть реализованы: перевод в радианы, приведение к диапазону 0–360,
сложение и вычитание углов, деление углов, получение значений тригонометрических функций, сравнение углов.
*/
#define MINUTE_IN_DEGREE 60
#define DEGREE_IN_CIRCLE 360
#define M_PI 3.14159265358979323846

#include <iostream>
#include <cmath>
#include <string> 
using namespace std;


class Angle {

public:
	Angle() : d(0), m(0), rad(0), otr(false) {}
	
	Angle(int degrees, int minutes) : d(degrees), m(minutes), otr(false) {
		rad = (degrees + (minutes/60)) * (M_PI/180);
	}

	int degree() const { return d; }
	int minute() const { return m; }
	double radian() const { return rad; }
	bool otric() const { return otr; }

	bool is_equal(const Angle& a) const {
		return d == a.degree() && m == a.minute();
	}

	friend istream& operator>> (istream& in, Angle& a);

private:
	int d, m;
	double rad;
	bool otr;
};

int is_number(const string& s) {//проверка входных данных
	bool otr = false;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == '-' && i == 0) {
			otr = true;
			continue;
		}
		else if (s[i] < '0' || s[i] > '9') { 
			return 0; 
		}
	}
	if (otr) { return 1; }
	else { return 2; }
}


//----------------Ввод вывод--------------------------------
istream& operator>> (istream& in, Angle& a) {
	cout << "Введите значение угла(состоящее из градусов и минут) в формате x.y:" << endl;
	string str, str_d, str_m;
	cin >> str; 

	bool point = false;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '.' && (i == 0 || i == str.length() - 1 || point == true)) {
			cout << "Ошибка! Некорректный ввод.\nПроверьте, правильно ли расставлены точки!" << endl;
			exit(4);
		}
		if (str[i] == '.' && i != 0 && i != str.length() - 1 && point == false) {
			point = true;
		}
		if (!point) {
			str_d.push_back(str[i]);
		}
		else if (point && str[i] != '.') {
			str_m.push_back(str[i]);
		}
	}
	if (point == false) {
		cout << "Ошибка! Некорректный ввод.\nОтсутствует минутная мера угла!" << endl;
		exit(5);
	}
	

	if (!is_number(str_d) || !is_number(str_m)) {
		cout << "Ошибка! Некорректный ввод." << endl;
		exit(1);
	}
	if (is_number(str_d) == 1) { a.otr = true; }
	a.d = stoi(str_d); a.m = stoi(str_m);
	if (a.m < 0) {
		cout << "Ошибка! Некорректный ввод.\nМинутная мера должна быть >0!" << endl;
		exit(2);
	}
	a.rad = (a.d + (a.m / 60)) * (M_PI / 180);
	return in;
}

ostream& operator<< (ostream& out, const Angle& a) {
	cout << a.degree() << "." << a.minute() << endl;
	return out;
}
//----------------ПЕРЕВОДЫ--------------------------------
int degrees_to_min(const Angle& a1) {
	if (a1.otric()) {
		return a1.degree() * 60 - a1.minute();
	}
	return a1.degree() * 60 + a1.minute();
}
Angle min_to_degrees(int min) {
	int new_d = min / 60;
	int new_m = min % 60;
	if (new_d < 0) {
		new_m *= (-1);
	}
	Angle cur(new_d, new_m);
	return cur;
}

Angle rangeDegrees(const Angle& a1) {//приведение к диапазону 0–360
	int new_d = a1.degree();
	int new_m = a1.minute();

	while (new_m > MINUTE_IN_DEGREE && !a1.otric()) {
		new_m -= MINUTE_IN_DEGREE;
		new_d++;
	}
	while (new_m > MINUTE_IN_DEGREE && a1.otric()) {
		new_m -= MINUTE_IN_DEGREE;
		new_d--;
	}
	
	if (abs(new_d) >= DEGREE_IN_CIRCLE) {
		if (a1.otric()) {
			new_d = DEGREE_IN_CIRCLE + new_d % DEGREE_IN_CIRCLE;
			if (new_m != 0) {
				new_m = MINUTE_IN_DEGREE - new_m;
			}
		}
		else if (!a1.otric()) {
			new_d = new_d % DEGREE_IN_CIRCLE;
		}
	}
	Angle cur(new_d, new_m);
	return cur;
}


//----------------МАТЕМАТИКА--------------------------------
double degrees_to_radians(Angle a1) {//перевод углов в радианы
	Angle cur = rangeDegrees(a1);
	double rad = degrees_to_min(a1) * (M_PI / (180 * 60));
	return rad;
}

bool cmpDegrees(const Angle& a1, const Angle& a2) { //сравнение углов(первый больше второго?)
	Angle cur1 = rangeDegrees(a1);
	Angle cur2 = rangeDegrees(a2);
	if (cur1.degree() > cur2.degree()) {
		return true;
	}
	else if (cur1.degree() == cur2.degree() && cur1.minute() > cur2.minute()) {
		return true;
	}
	else {
		return false;
	}
}

Angle operator+ (const Angle& a1, const Angle& a2) {
	int res = degrees_to_min(a1) + degrees_to_min(a2);
	Angle cur = rangeDegrees(min_to_degrees(res));
	return cur;
}

Angle operator- (const Angle& a1, const Angle& a2) {
	int res = degrees_to_min(a1) - degrees_to_min(a2);
	Angle cur = rangeDegrees(min_to_degrees(res));
	return cur;
}

Angle operator* (const Angle& a1, int multipli) {
	int res = degrees_to_min(a1) * multipli;
	Angle cur = rangeDegrees(min_to_degrees(res));
	return cur;
}

Angle operator/ (const Angle& a1, int div) {
	if (div == 0) {
		cout << "На 0 делить нельзя!" << endl;
		exit(3);
	}
	int new_d = a1.degree() / div;
	if (div < 0) {
		div *= -1;
	}
	int new_m = a1.minute() / div;
	Angle res(new_d, new_m);
	Angle cur = rangeDegrees(res);
	return cur;
}

//----------------ТРИГОНОМЕТРИЯ--------------------------------
double sinDegrees(const Angle& a1) {//синус угла
	return sin(a1.radian());
}

double cosDegrees(const Angle& a1) {//косинус угла
	return cos(a1.radian());
}

double tgDegrees(const Angle& a1) {//тангенс угла
	return sinDegrees(a1) / cosDegrees(a1);
}

double ctgDegrees(const Angle& a1) {//котангенс угла
	return 1 / tgDegrees(a1);
}


//////////////////////////////////////////////////////////////////////////
int main() {
	setlocale(LC_ALL, "rus");
	Angle a1, a2;
	cin >> a1 >> a2;
	
	cout << "Введите число для демонстрации функций сложения и умножения" << endl;
	int num;
	cin >> num;
	cout << "---------------------------------------------------" << endl;

	cout << endl << "Ваши углы:" << endl;
	cout  << "a1 = " << a1 << "a2 = " << a2;
	cout << "num: "  << num << endl ;

	cout << endl << "Приведение к диапазону 0–360: " << endl;
	cout << "a1 = " << rangeDegrees(a1);
	cout << "a2 = " << rangeDegrees(a2) << endl;
	
	cout << "Сравнение углов:" << endl;
	if (a1.is_equal(a2)) {
		cout << "Углы равны" << endl;
	}
	else {
		cmpDegrees(a1, a2) ? cout << " > " << endl : cout << " < " << endl;
	}

	cout << "a1 + a2 = " << a1 + a2;
	cout << "a1 - a2 = " <<  a1 - a2;
	cout << "a1 * num = " << a1 * num;
	cout << "a1 / num = " << a1 / num;

	cout << endl << "Перевод углов в радианы:" << endl;
	cout << "a1 = " << degrees_to_radians(a1) << endl;
	cout << "a2 = " << degrees_to_radians(a2) << endl;

	cout << endl << "Синус угла a1 = " << sinDegrees(a1) << endl;
	cout << endl << "Косинус угла a1 = " << cosDegrees(a1) << endl;
	cout << endl << "Тангенс угла a1 = " << tgDegrees(a1) << endl;
	cout << endl << "Котангенс угла a1 = " << ctgDegrees(a1) << endl;
}