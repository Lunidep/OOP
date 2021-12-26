#ifndef _D_FACTORY_H_ 
#define _D_FACTORY_H_

#include <memory>
#include <fstream>
#include <string>
#include "figure.h"

#include "square.h"
#include "octagon.h"
#include "triangle.h"

struct factory {
    shared_ptr<figure> new_figure(istream& is);
};

#endif
