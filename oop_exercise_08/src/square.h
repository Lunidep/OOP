#ifndef _D_SQUARE_H_
#define _D_SQUARE_H_

#include "figure.h"

class square : public figure {
public:
    square() = default; 
    square(istream& is);
    double area() const override;
    ostream& print(ostream&) const override;
private:
    double side;
};

#endif
 