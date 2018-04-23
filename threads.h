#ifndef THREADS_H
#define THREADS_H

#include "thread_base.h"
#include "typedefs.h"
#include <mutex>


static std::mutex threadA_mutex;
static std::mutex threadB_mutex;


class ThreadA: public ThreadBase
{
private:
    _tblocks& m_blocks;
    size_t m_blk_count;
    size_t m_blksize;

public:
    ThreadA(_tblocks& blocks, size_t block_count, size_t size);
    virtual ~ThreadA(){}

    virtual void proccess();
};


class ThreadB: public ThreadBase
{
private:
    _tblocks& m_blocks;
    _tcrcs_per_block& m_crcs_per_block;
    size_t m_blk_count;
    size_t m_cur_block_idx;
public:
    ThreadB(_tblocks& blocks, _tcrcs_per_block& crcs_per_block, size_t block_count);
    virtual ~ThreadB(){}

    virtual void proccess();

};

#endif // THREADS_H
