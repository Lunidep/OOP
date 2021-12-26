#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <cstdint>
#include <memory>
#include <string> 
#include <algorithm>
#include <vector>

#include "figure.h"
#include "factory.h"

struct document {
public:
    void Print() const ; 
    document(string& newName): name_(newName), factory_(), buffer_(0) {};
    void Insert(shared_ptr<figure>& ptr);
    void Rename(const string& newName);
    void Save(const string& filename) const;
    void Load(const string& filename);
    shared_ptr<figure> GetFigure(uint32_t index);
    void Erase(uint32_t index);
    string GetName();
    size_t Size();
private:
    friend class InsertCommand;
    friend class DeleteCommand;
    factory factory_;
    string name_;
    vector<shared_ptr<figure>> buffer_;
    void RemoveLast();
    void InsertIndex(shared_ptr<figure>& newFigure, uint32_t index);
};


#endif
