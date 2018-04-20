#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include <thread>

class ThreadBase
{
private:
    std::thread thr;
public:
    ThreadBase()
    {
        thr = std::thread(&ThreadBase::proccess, this);
    }
    virtual ~ThreadBase()
    {
        if(thr.joinable())
            thr.join();
    }
    virtual void proccess()= 0;

};

#endif // THREAD_BASE_H
