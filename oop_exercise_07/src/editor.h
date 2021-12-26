#ifndef _D_EDITOR_H_
#define _D_EDITOR_H_

#include <stack>
#include "command.h"

struct editor {
private:
    shared_ptr<document> doc_;
    stack<shared_ptr<Acommand>> history_;
public:
    ~editor() = default; 
    void PrintDocument();
    void CreateDocument(string& newName);
    bool DocumentExist();
    editor() : doc_(nullptr), history_() {}
    void InsertInDocument(shared_ptr<figure>& newFigure);
    void DeleteInDocument(uint32_t index);
    void SaveDocument();
    void LoadDocument(string& name);
    void Undo();
};

#endif