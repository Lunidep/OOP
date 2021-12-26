#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <memory>
#include <iostream>
#include <fstream>
#include <string>

#include "hexagon.h"
#include "pentagon.h"
#include "octagon.h"

struct factory {
    shared_ptr<figure> FigureCreate(istream& is);
    shared_ptr<figure> FigureCreateFile(ifstream& is); 
};

#endif
