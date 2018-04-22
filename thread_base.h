#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include <thread>

class ThreadBase
{
private:
    std::thread m_thr;
public:
    bool m_stop;
    ThreadBase():
    m_stop(false)
    {
        m_thr = std::thread(&ThreadBase::proccess, this);
    }
    virtual void Wait()
    {
        if(m_thr.joinable())
            m_thr.join();
    }
    virtual Stop()
    {
        m_stop = true;
    }
    virtual ~ThreadBase()
    {
        m_stop=true;
        if(m_thr.joinable())
            m_thr.join();
    }
    virtual void proccess()= 0;

};

#endif // THREAD_BASE_H
