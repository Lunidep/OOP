#include "square.h"

square::square(istream& is) {
    string str;
    cout << "side = ";  is >> str; cout << endl;

    while (true) {
        if (is_fig_num(str)) {
            side = stod(str);
            break;
        }
        cout << "Square input error!\n";
        cout << "Repeat input!\n";
        cout << "side = ";  is >> str; cout << endl;
    }
}

double square::area() const {
    long double res = pow(side, 2);
    return res;
}

ostream& square::print(ostream& os) const {
    os << endl << "Square" << endl;
    os << "Side = " << side << endl;
    os << "Area = " << area() << '\n'; 

    return os;
}
