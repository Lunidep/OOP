#ifndef _D_TRIANGLE_H_
#define _D_TRIANGLE_H_

#include "figure.h"

class triangle : public figure {
public:
    triangle() = default;
    triangle(istream& is);
    double area() const override;
    ostream& print(ostream& os) const override;
private:
    double a, h;
};

#endif
