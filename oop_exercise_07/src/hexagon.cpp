#include "hexagon.h"

void hexagon::print(ostream& os) const {
    os << "Hexagon\n";
    os << "Side = " << side;
    os << "\nArea:" << area() << '\n';
}

void hexagon::printFile(ofstream& of) const {
    of << "hexagon\n" << side << '\n';
}

double hexagon::area() const{
    long double res = (double)((3 * sqrt(3)) / 2) * pow(side, 2);
    return res;
}

hexagon::hexagon(istream& is) {
    string str;
    cout << "side = ";  is >> str; cout << endl;

    while (true) {
        if (is_fig_num(str)) {
            side = stod(str);
            break;
        }
        cout << "Hexagon input error!\n";
        cout << "Repeat input!\n";
        cout << "side = ";  is >> str; cout << endl;
    }
}

hexagon::hexagon(ifstream& is) {
    is >> side;
}
