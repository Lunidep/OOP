/*
Вариант 18:
Контейнер - Бинарное- Дерево

Необходимо спроектировать и запрограммировать на языке C++ класс-контейнер первого уровня, содержащий одну фигуру (одна из фигур ЛР3 на выбор). 
Вариант структуры данных для контейнера выбрать из документа “Варианты структур данных”  
(контейнер 1-го уровня) согласно своему номеру из  Варианты ЛР4..
*/

#include <iostream>
#include <vector>
#include <string> 
#include <cmath>
using namespace std;

#include "BinTree.h"

bool is_number(const string& s) {
    bool point = false;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '-' && i == 0) {
            continue;
        }
        else if (s[i] == '.') {
            if ((i == 0 || i == s.length() - 1) || point) {
                return false;
            }
            else {
                point = true;
            }
        }
        else if (s[i] < '0' || s[i] > '9') { return false; }
    }
    return true;
}

class Point {
private:
    double x;
    double y;
public:
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    double getX() const { return x; }
    double getY() const { return y; }
    friend istream& operator>> (istream& in, Point& p);
};

istream& operator>> (istream& in, Point& p) {

    string _x, _y; cin >> _x >> _y;

    if (!is_number(_x) || !is_number(_y)) {
        throw invalid_argument("Ошибка!Некорректный ввод.\n");
        //cout << "Ошибка! Некорректный ввод.\n";
        //exit(1);
    }

    p.x = stod(_x); p.y = stod(_y);
    return in;

}
ostream& operator<< (ostream& out, const Point& p) {
    cout << "(" << p.getX() << ", " << p.getY() << ")  ";
    return out;

}

double fabss(double a) {
    if (a >= 0) { return a; }
    else { return -a; }
}

double koef_nakl(const Point& a, const Point& b) {
    double k = (a.getY() - b.getY()) / (a.getX() - b.getX());
    return k;
}
bool trapezoid_check(const Point& a, const Point& b, const Point& c, const Point& d) {
    //case 1: ab || cd
    if (koef_nakl(a, b) == koef_nakl(c, d)) { return true; }
    //case 2: bc || ad
    else if (koef_nakl(b, c) == koef_nakl(d, a)) { return true; }
    return false;
}

class Trapezoid {
    Point a, b, c, d;
    vector<Point> v;
public:
    Trapezoid(Point _a, Point _b, Point _c, Point _d) : a(_a), b(_b), c(_c), d(_d) {
        v.push_back(_a);
        v.push_back(_b);
        v.push_back(_c);
        v.push_back(_d);
    }

    ~Trapezoid() {}

    double Area() const {
        double cur_res = 0;
        double res = 0;
        int i;
        for (i = 0; i < v.size() - 1; i++) {
            cur_res += v[i].getX() * v[i + 1].getY() - v[i].getY() * v[i + 1].getX();
        }

        cur_res += v[i].getX() * v[0].getY() - v[i].getY() * v[0].getX();

        res = fabss(cur_res) / 2;
        return res;
    }

    Point Geometric_center() const {
        double sumX = 0;
        double sumY = 0;
        for (int i = 0; i < v.size(); i++) {
            sumX += v[i].getX();
            sumY += v[i].getY();
        }
        Point a(sumX / v.size(), sumY / v.size());
        return a;
    }

    void Coordinates() const {
        cout << a << b << c << d;
    }

    void print() const {
        cout << "Coordinates: ";
        this->Coordinates();
        cout << "Area: " << this->Area();
        /*
        cout << "---------------------------------------------\n";
        cout << "|  Площадь: " << this->Area() << endl;
        Point cur = this->Geometric_center();
        cout << "|  Геометрический центр:\n" << "|  x = " << cur.getX() << "\n|  y =  " << cur.getY() << endl;
        cout << "|  Координаты: ";
        this->Coordinates();
        cout << "\n---------------------------------------------";
        */
    }
};

bool operator< (const Trapezoid& a, const Trapezoid& b) {
    if (a.Area() < b.Area()) return true;
    else return false;
}

bool operator<= (const Trapezoid& a, const Trapezoid& b) {
    if (a.Area() <= b.Area()) return true;
    else return false;
}

bool operator> (const Trapezoid& a, const Trapezoid& b) {
    if (a.Area() > b.Area()) return true;
    else return false;
}

bool operator>= (const Trapezoid& a, const Trapezoid& b) {
    if (a.Area() >= b.Area()) return true;
    else return false;
}

bool operator== (const Trapezoid& a, const Trapezoid& b) {
    if (a.Area() == b.Area()) return true;
    else return false;
}

ostream& operator<< (ostream& out, const Trapezoid& t) {
    t.print();
    return out;

}

void menu() {
    cout << "Доступные функции:\nadd - добавить фигуру\nget - получить фигуру\ndel - удалить фигуру\nmenu - вывести меню повторно\nexit - выход\n\n\n";
}

int main() {
	setlocale(LC_ALL, "rus");

    /*
    Point a(0, 0);
    Point b(0, 1);
    Point c(1, 1);
    Point d(6, 0);

    Point a1(0, 0);
    Point b1(0, 1);
    Point c1(1, 1);
    Point d1(8, 0);

    Point a2(0, 0);
    Point b2(0, 1);
    Point c2(1, 1);
    Point d2(5, 0);

    Point a3(0, 0);
    Point b3(0, 1);
    Point c3(1, 1);
    Point d3(7, 0);

    Point a4(0, 0);
    Point b4(0, 1);
    Point c4(1, 1);
    Point d4(9, 0);

    Trapezoid t(a, b, c, d);

    Trapezoid t1(a1, b1, c1, d1);

    Trapezoid t2(a2, b2, c2, d2);

    Trapezoid t3(a3, b3, c3, d3);

    Trapezoid t4(a4, b4, c4, d4);

    BinTree<Trapezoid> tree;
    
    tree.insert(t);
    tree.insert(t1);
    tree.insert(t2);
    tree.insert(t3);
    tree.insert(t4);
    

    tree.rec_s("r");
    //tree.remove(t);

    tree.print();
*/

    BinTree<Trapezoid> tree;
    string str, path;
    bool exit = false;
    menu();


    while (!exit) {
        try {
            cin >> str;
            if (str == "add") {
                Point a1, b1, c1, d1;
                cout << "Введите в порядке последовательного обхода фигуры точки в вида x y\n";
                cin >> a1 >> b1 >> c1 >> d1;
                if (trapezoid_check(a1, b1, c1, d1)) {
                    tree.insert(Trapezoid(a1, b1, c1, d1));
                    cout << "Фигура успешно добавлена в дерево\n\n";
                }
                else {
                    throw invalid_argument("Введенная фигура не является трапецией\n\n");
                }
            }
            else if (str == "get") {
                if (tree.empty()) {
                    throw invalid_argument("В дереве нет элементов!\n\n");
                }
                else {
                    tree.print();
                    cout << "Введите путь до желаемой фигуры (в формате lrl...)\nЕсли необходимо удалить корень, введите 'root'\n\n";
                    cin >> path;
                    if (path == "root") {
                        tree.get("");
                    }
                    else {
                        tree.get(path);
                    }
                }
            }
            else if (str == "del") {
                if (tree.empty()) {
                    throw invalid_argument("В дереве нет элементов!\n\n");
                }
                else {
                    tree.print();
                    cout << "Введите путь до желаемой фигуры (в формате lrl...)\nЕсли необходимо удалить корень, введите 'root'\n\n";
                    cin >> path;
                    if (path == "root") {
                        tree.remove("");
                    }
                    else {
                        tree.remove(path);
                    }
                }
            }
            else if (str == "print") {
                tree.print();
                //cout << tree;
            }
            else if (str == "menu") {
                menu();
            }
            else if (str == "exit") {
                cout << "Завершение работы\n\n";
                exit = true;
            }
            else {
                throw invalid_argument("Некорректный ввод\n\n");
            }
        }
        catch (invalid_argument& arg) {
            cout << arg.what() << endl;
        }
    }

    return 0;
}