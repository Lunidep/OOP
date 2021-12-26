#include "factory.h"

shared_ptr<figure> factory::new_figure(istream &is) { 
    string name;
    is >> name;
    if (name == "square") {
        return shared_ptr<figure> ( new square(is));
    } else if ( name == "triangle") {
        return shared_ptr<figure> ( new triangle(is));
    } else if ( name == "octagon") {
        return shared_ptr<figure> ( new octagon(is));
    } else {
        throw logic_error("Error figure type!\n\n");
    }
}


