#include "processor.h"

void stream_processor::process(shared_ptr<vector<shared_ptr<figure>>> buffer) {
    for (auto figure : *buffer) {
        figure->print(cout);
    }
}

void file_processor::process(shared_ptr<vector<shared_ptr<figure>>> buffer) {
    ofstream fout;
    fout.open(to_string(cnt) + ".txt"); 
    cnt++;
    if (!fout.is_open()) {
        cout << "can't open\n";
        return;
    }
    for (auto figure : *buffer) {
        figure->print(fout);
    }
}

