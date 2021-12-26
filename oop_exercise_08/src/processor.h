#ifndef _D_PROCESSOR_H_ 
#define _D_PROCESSOR_H_

#include <condition_variable>
#include <thread>
#include <vector>
#include <mutex>

#include "figure.h"
#include "factory.h"
 
struct processor {
    virtual void process(shared_ptr<vector<shared_ptr<figure>>> buffer) = 0;
};

struct stream_processor : processor {
    void process(shared_ptr<vector<shared_ptr<figure>>> buffer) override;
};

struct file_processor : processor {
    void process(shared_ptr<vector<shared_ptr<figure>>> buffer) override;
private:
    int cnt = 0;
};

#endif // _D_PROCESSOR_H_
