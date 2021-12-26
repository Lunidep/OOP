#ifndef _D_FIGURE_H_
#define _D_FIGURE_H_

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct figure {
    virtual ostream& print(ostream& os) const = 0; 
    virtual double area() const = 0;
    virtual ~figure() {}

    virtual bool is_fig_num(const string& s) {
        bool point = false;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '.') {
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
};

#endif