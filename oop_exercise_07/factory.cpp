#include "factory.h" 

shared_ptr<figure> factory::FigureCreate(istream &is) {
    string name;
    is >> name;
    if (name == "hexagon" ) {
        return shared_ptr<figure> ( new hexagon(is));
    } else if (name == "pentagon") {
        return shared_ptr<figure> ( new pentagon(is));
    } else if (name == "octagon") {
        return shared_ptr<figure> ( new octagon(is));
    } else {
        throw logic_error("There is no such figure!\n");
    }
}

shared_ptr<figure> factory::FigureCreateFile(ifstream &is) {
    string name;
    is >> name;
    if (name == "hexagon" ) {
        return shared_ptr<figure> (new hexagon(is));
    } else if (name == "pentagon") {
        return shared_ptr<figure> (new pentagon(is));
    } else if (name == "octagon") {
        return shared_ptr<figure> (new octagon(is));
    } else {
        throw logic_error("There is no such figure!\n");
    }
}