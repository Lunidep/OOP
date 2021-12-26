#include "subscriber.h"

void subscriber::operator()() {
    while(!stop){
        unique_lock<mutex>lock(mtx);
        cond_var.wait(lock,[&]{ return (buffer != nullptr || stop);});
        
        for (auto elem: processors) {
            elem->process(buffer);
        }

        buffer = nullptr;
        cond_var.notify_all();
    } 
}