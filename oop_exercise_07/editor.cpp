#include "editor.h" 

void editor::PrintDocument() {
    if (doc_ == nullptr) {
        cout << "No document!\n\n";
        return;
    }
    doc_->Print();
}

void editor::CreateDocument(string &newName) {
    doc_ = make_shared<document>(newName);
}

bool editor::DocumentExist() {
    return doc_ != nullptr;
}

void editor::InsertInDocument(shared_ptr<figure> &newFigure) {
    if (doc_ == nullptr) {
        cout << "No document!\n\n";
        return;
    }
    shared_ptr<Acommand> command = shared_ptr<Acommand>(new InsertCommand(doc_));
    doc_->Insert(newFigure);
    history_.push(command);
    cout << "Add success!\n\n";
}

void editor::DeleteInDocument(uint32_t index) {
    if (doc_ == nullptr) {
        cout << "No document!\n\n";
        return;
    }
    if (index >= doc_->Size()) {
        cout << "Index error!\n\n";
        return;
    }
    shared_ptr<figure> tmp = doc_->GetFigure(index);
    shared_ptr<Acommand> command = shared_ptr<Acommand>(new DeleteCommand(tmp,index,doc_));
    doc_->Erase(index);
    history_.push(command);
    cout << "Remove success\n\n";
}

void editor::SaveDocument() {
    if (doc_ == nullptr) {
        cout << "No document!\n\n";
        return;
    }
    string saveName = doc_->GetName();
    doc_ ->Save(saveName);
    cout << "Save success\n\n";
}

void editor::LoadDocument(string &name) {
    try {
        doc_ = make_shared<document>(name);
        doc_->Load(name);
        while (!history_.empty()){
            history_.pop();
        }
    } catch(logic_error& e) {
        cout << e.what();
    }
}

void editor::Undo() {
    if (history_.empty()) {
        throw logic_error("History is empty!\n\n");
    }
    shared_ptr<Acommand> lastCommand = history_.top();
    lastCommand->UnExecute();
    history_.pop();
}
