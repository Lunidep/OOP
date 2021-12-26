#include "octagon.h"

octagon::octagon(istream& is) {
    string str;
    cout << "side = ";  is >> str; cout << endl;
    
    while (true) {
        if (is_fig_num(str)) {
            side = stod(str);
            break;
        }
        cout << "Octagon input error!\n";
        cout << "Repeat input!\n";
        cout << "side = ";  is >> str; cout << endl;
    }
}

double octagon::area() const {
    long double res = (2 + 2 * sqrt(2)) * pow(side, 2);
    return res;
}

ostream& octagon::print(ostream& os) const {
    os << endl << "Octagon" << endl;
    os << "Side = " << side << endl;
    os << "Area = " << area() << '\n';

    return os;
}