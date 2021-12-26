/*
����� ����
������ �80-206�-20
������� 20:
    ��������
    ����
    5-��������

����������� ������ �������� �������� �������, ������ ������  ������������� �� �������� ������ Figure.

��� ������ ������ ������������ ����� ����� ������� :
    ���������� ��������������� ������ ������.
    ����� � ����������� ����� ������ std::cout ��������� ������ ������;
    ���������� ������� ������.

��������� ������ ����� ��������� ����������� :
    ������� �� ������������ ����� std::cin ������, �������� �������� �������.
    ��������� ��������� ������ � ������������ ������ std::vector<Figure*>.
    �������� ��� ����� ������� ����� �������(1 - 3 ��.����), �.�.������������� ��� ������ ������ � ������� �������������� �����, ���������� ������ � �������.
    ��������� ����� ������� ����� � �������.
    ������� �� ������� ������ �� �������.
*/
#include <iostream>
#include <cmath>
#include <string> 
#include <vector> 
using namespace std;

bool is_number(const string& s) {//�������� ������������ �������� ���������
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

class Point {//����� �����, � �������������� ����������� ����� � ������
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
        cout << "������! ������������ ����.\n";
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

double calc_area(const vector<Point>& v) {//�������, ��������� ������� ��� ���� �����
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

Point calc_geom_center(const vector<Point>& v) {//�������, ��������� ���� ����� ��� ���� �����
    double sumX = 0;
    double sumY = 0;
    for (int i = 0; i < v.size(); i++) {
        sumX += v[i].getX();
        sumY += v[i].getY();
    }
    Point a(sumX / v.size(), sumY / v.size());
    return a;
}

double dlina(const Point& a, const Point& b) {
    return sqrt(pow((b.getX() - a.getX()), 2) + pow((b.getY() - a.getY()), 2));
}



class Figure {//������������ ����� ������ � ������������ ��������
public:
    virtual double Area() const = 0;//������� �������
    virtual Point Geometric_center() const = 0;//����� ���� ������
    virtual void Coordinates() const = 0;//����� ��������� �����
    virtual ~Figure() {}
};

class Trapezoid : public Figure {//����������� ����� ��������
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
        return calc_area(v);
    }
    Point Geometric_center() const {
        return calc_geom_center(v);
    }
    void Coordinates() const {
        cout << a << b << c << d;
    }
};

class Rhomb : public Figure {//����������� ����� ����
    Point a, b, c, d;
    vector<Point> v;
public:
    Rhomb(Point _a, Point _b, Point _c, Point _d) : a(_a), b(_b), c(_c), d(_d) {
        v.push_back(_a);
        v.push_back(_b);
        v.push_back(_c);
        v.push_back(_d);
    }
    ~Rhomb() {}
    double Area() const {
        return calc_area(v);
    }
    Point Geometric_center() const {
        return calc_geom_center(v);
    }
    void Coordinates() const {
        cout << a << b << c << d;
    }
};

class Pentagon : public Figure {//����������� ����� ������������
    Point a, b, c, d, e;
    vector<Point> v;
public:
    Pentagon(Point _a, Point _b, Point _c, Point _d, Point _e) : a(_a), b(_b), c(_c), d(_d), e(_e) {
        v.push_back(_a);
        v.push_back(_b);
        v.push_back(_c);
        v.push_back(_d);
        v.push_back(_e);
    }
    ~Pentagon() {}
    double Area() const {
        return calc_area(v);
    }
    Point Geometric_center() const {
        return calc_geom_center(v);
    }
    void Coordinates() const {
        cout << a << b << c << d << e;
    }
};



void menu() {
    cout << "\n��������� �������:\nadd - �������� ������\ndel - ������� ������\nshow - ������������� ��� ������ ������ � ������� ��� �� ��������������\nsum - ��������� ��������� ������� ���� ����� � �������\nmenu - ������� ���� ��������\nexit - �����\n\n\n";
}

double koef_nakl(const Point& a, const Point& b) {//�������� �������, ����������� �������������� ������
    double k = (a.getY() - b.getY()) / (a.getX() - b.getX());
    //cout << k << endl;
    return k;
}

bool trapezoid_check(const Point& a, const Point& b, const Point& c, const Point& d) {//�������� ��������� ������ �� ��, �������� �� ��� ���������
    Trapezoid t(a, b, c, d);
    if (t.Area() == 0) {
        return false;
    }

    //case 1: ab || cd
    if (koef_nakl(a, b) == koef_nakl(c, d)) { return true; }
    //case 2: bc || ad
    else if (koef_nakl(b, c) == koef_nakl(a, d)) { return true; }
    return false;
}

bool rhomb_check(const Point& a, const Point& b, const Point& c, const Point& d) {//�������� ��������� ������ �� ��, �������� �� ��� ������
    if (dlina(a, b) == dlina(b, c) && dlina(c, d) == dlina(a, d) && dlina(b, c) == dlina(c, d)) { return true; }
    return false;
}



int main() {
    setlocale(LC_ALL, "rus");
    vector<Figure*> vf;
    string str, fig;
    bool exit = false;
    menu();
    while (!exit) {
        cin >> str;
        if (str == "add") {
            cout << "\n�������� ��� ������:\nt - ��������\nr - ����\np - ������������\n";
            cin >> fig;
            if (fig == "t") {
                Point a1, b1, c1, d1;
                cout << "������� � ������� ����������������� ������ ������ ����� � ���� x y\n";
                cin >> a1 >> b1 >> c1 >> d1;
                if (trapezoid_check(a1, b1, c1, d1)) {
                    vf.push_back(new Trapezoid(a1, b1, c1, d1));
                    cout << "������ ������� ���������\n";
                }
                else {
                    cout << "��������� ������ �� �������� ���������\n";
                }
            }
            else if (fig == "r") {
                Point a1, b1, c1, d1;
                cout << "������� � ������� ����������������� ������ ������ ����� � ���� x y\n";
                cin >> a1 >> b1 >> c1 >> d1;
                if (rhomb_check(a1, b1, c1, d1)) {
                    vf.push_back(new Rhomb(a1, b1, c1, d1));
                    cout << "������ ������� ���������\n";
                }
                else {
                    cout << "��������� ������ �� �������� ������\n";
                }
            }
            else if (fig == "p") {
                Point a1, b1, c1, d1, e1;
                cout << "������� � ������� ����������������� ������ ������ ����� � ���� x y\n";
                cin >> a1 >> b1 >> c1 >> d1 >> e1;
                vf.push_back(new Pentagon(a1, b1, c1, d1, e1));
                cout << "������ ������� ���������\n";
            }
            else {
                cout << "������������ ����!\n\n\n";
            }
        }
        else if (str == "show") {
            for (int i = 0; i < vf.size(); i++) {
                cout << "������� ������ � �������� " << i << ": " << vf[i]->Area() << endl;
                Point cur = vf[i]->Geometric_center();
                cout << "�������������� ����� ������ � �������� " << i << ": " << "x = " << cur.getX() << "  y =  " << cur.getY() << endl;
                cout << "���������� ������ � �������� " << i << ": ";
                vf[i]->Coordinates();
                cout << "\n--------------------------------------------------------------\n";
            }
        }
        else if (str == "sum") {
            double sum = 0;
            for (int i = 0; i < vf.size(); i++) {
                sum += vf[i]->Area();
            }
            cout << sum << endl;
        }
        else if (str == "del") {
            int n, i;
            cout << "������� ������ ���������� ��������\n";
            cin >> n;
            if (vf.size() > n){

                delete vf[n];
                vf.erase(vf.begin() + n);
            }
            else {
                cout << "������� �������� � ������� ���!\n";
            }
        }
        else if (str == "menu") {
            menu();
        }
        else if (str == "exit") {
            cout << "���������� ������\n";
            exit = true;
        }
        else {
            cout << "������������ ����!\n\n\n";
        }
    }
}

/*
* �������� ��������
///////////////////////////////////
add t
0 0
0 4
2 4
6 0

add r
0 0
-1 2
0 4
1 2

add p
0 0
-4 3
-2 4
2 4
4 3
//////////////////////////////////////
add t
-1 0
-4 5
8 5
2.7 0

add r
0 1
1.1 0
0 -1.1
-1 0

add p
1 1
7.5 1
8 -1
2 -3.5
-1 -1
*/