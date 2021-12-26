#include "octagon.h"

void octagon::print(ostream& os) const {
    os << "Octagon\n";
    os << "Side = " << side;
    os << "\nArea:" << area() << '\n';
}

void octagon::printFile(ofstream& of) const {
    of << "octagon\n" << side << '\n';
}

double octagon::area() const {
    long double res = (2 + 2 * sqrt(2)) * pow(side, 2);
    return res;
}

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

octagon::octagon(ifstream& is) {
    is >> side;
}