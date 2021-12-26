#include "triangle.h" 

triangle::triangle(istream &is) {
    string str1, str2;

    cout << "a = "; is >> str1;
    cout << "h = "; is >> str2; cout << endl;

    while(true) {
        if (is_fig_num(str1) && is_fig_num(str2)) {
            a = stod(str1);
            h = stod(str2);
            break;
        }
        cout << "Triangle input error!\n";
        cout << "Repeat input!\n";
        cout << "a = "; is >> str1;
        cout << "h = "; is >> str2; cout << endl;
    }
};

double triangle::area() const {
    double res = 0.5 * a * h;
    return res;
}

ostream& triangle::print(ostream& os) const {
    os << endl << "Triangle" << endl;
    os << "a = " << a << endl;
    os << "h = " << h << endl;
    os << "Area = " << area() << '\n';
    return os;
}

