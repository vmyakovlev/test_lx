#ifndef THREADS_H
#define THREADS_H

#include "thread_base.h"
#include "typedefs.h"
#include <mutex>


static std::mutex print_mutex;

static std::mutex add_mutex;

class ThreadA: private ThreadBase
{
private:
    _tblocks& blocks;
    size_t blk_count;
    size_t blksize;

public:
    ThreadA(_tblocks& blocks, size_t block_count, size_t size);
    virtual ~ThreadA();

    virtual void proccess();
};




class ThreadB: private ThreadBase
{
private:
    _tblocks& blocks;
    size_t blk_count;
    size_t cur_block_idx;
public:
    ThreadB(_tblocks& blocks, size_t block_count);
    virtual ~ThreadB();

    virtual void proccess();

};

#endif // THREADS_H
