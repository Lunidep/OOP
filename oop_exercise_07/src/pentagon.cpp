#include "pentagon.h"

void pentagon::print(ostream& os) const {
    os << "Pentagon\n";
    os << "Side = " << side;
    os << "\nArea:" << area() << '\n';
} 

void pentagon::printFile(ofstream &of) const {
    of << "pentagon\n"<< side << '\n';
}

double pentagon::area() const {
    long double cur = (double)pow(side, 2) / (double)4;
    long double res = cur * sqrt(25 + 10 * sqrt(5));
    return res;
}

pentagon::pentagon(istream& is) {
    string str;
    cout << "side = ";  is >> str; cout << endl;

    while (true) {
        if (is_fig_num(str)) {
            side = stod(str);
            break;
        }
        cout << "Pentagon input error!\n";
        cout << "Repeat input!\n";
        cout << "side = ";  is >> str; cout << endl;
    }
}

pentagon::pentagon(ifstream& is) {
    is >> side;
}