#ifndef _D_octagon_H_
#define _D_octagon_H_

#include "figure.h"

class octagon : public figure {
public:
    octagon() = default;
    octagon(istream& is);
    double area() const override;
    ostream& print(ostream& os) const override;
private:
    double side; 
};

#endif
