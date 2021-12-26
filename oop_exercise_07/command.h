#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "document.h"

struct Acommand {
public:
    virtual ~Acommand() = default; 
    virtual void UnExecute() = 0;
protected:
    shared_ptr<document> doc_;
};

struct InsertCommand : public Acommand {
public:
    void UnExecute() override;
    InsertCommand(shared_ptr<document>& doc);
};

struct DeleteCommand : public Acommand {
public:
    DeleteCommand(shared_ptr<figure>& newFigure, uint32_t newIndex,shared_ptr<document>& doc);
    void UnExecute() override;
private:
    shared_ptr<figure> figure_;
    uint32_t index_;
};
#endif
