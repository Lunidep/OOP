#include "document.h"

void document::Print() const {
    if (buffer_.empty()) {
        cout << "Buffer is empty!\n";
    }
    for (auto elem : buffer_) {
        elem->print(cout);
    }
}

void document::Insert(shared_ptr<figure> &ptr) {
    buffer_.push_back(ptr); 
}

void document::Rename(const string &newName) {
    name_ = newName;
}

void document::Save(const string &filename) const {
    ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        throw runtime_error("File is not opened!\n");
    }
    fout << buffer_.size() << '\n';
    for (auto elem : buffer_) {
        elem->printFile(fout);
    }
}

void document::Load(const string &filename) {
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        throw runtime_error("File is not opened!\n");
    }
    size_t size;
    fin >> size;
    buffer_.clear();
    for (int i = 0; i < size; ++i) {
        buffer_.push_back(factory_.FigureCreateFile(fin));
    }
    name_ = filename;
}

shared_ptr<figure> document::GetFigure(uint32_t index) {
    return buffer_[index];
}

void document::Erase(uint32_t index) {
    if ( index >= buffer_.size()) {
        throw logic_error("Out of bounds!\n");
    }
    buffer_[index] = nullptr;
    for (; index < buffer_.size() - 1; ++index) {
        buffer_[index] = buffer_[index + 1];
    }
    buffer_.pop_back();
}

string document::GetName() {
    return this->name_;
}

size_t document::Size() {
    return buffer_.size();
}

void document::RemoveLast() {
    if (buffer_.empty()) {
        throw logic_error("Document is empty!");
    }
    buffer_.pop_back();
}

void document::InsertIndex(shared_ptr<figure> &newFigure, uint32_t index) {
    buffer_.insert(buffer_.begin() + index, newFigure);
}
