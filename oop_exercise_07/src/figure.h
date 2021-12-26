#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <iostream> 
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct figure {
    virtual void print(ostream&) const = 0 ;
    virtual void printFile(ofstream&) const = 0 ;
    virtual double area() const = 0;
    virtual ~figure() = default;
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
