#ifndef _D_SUBSCTIBER_H_ 
#define _D_SUBSCTIBER_H_

#include "processor.h"

struct subscriber {
    void operator()();
    vector<shared_ptr<processor>> processors; 
    shared_ptr<vector<shared_ptr<figure>>> buffer;
    mutex mtx;
    condition_variable cond_var;
    bool stop = false;
};

#endif
