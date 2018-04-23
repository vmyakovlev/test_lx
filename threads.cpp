
#include <iostream>
#include <random>

#include "threads.h"

//*************************************************************************************
ThreadA::ThreadA(_tblocks& blocks, size_t block_count, size_t size):
    m_blocks(blocks),
    m_blk_count(block_count),
    m_blksize(size)
{

}

//*************************************************************************************
void ThreadA::proccess()
{
    std::random_device rd;
    std::minstd_rand gen(rd());
    while (m_blocks.size()<m_blk_count && !m_stop) {
        _telement* block = new _telement(m_blksize);

        for(auto& elem: *block)
            elem = gen();

        threadA_mutex.lock();
        if (m_blocks.size()<m_blk_count)
            m_blocks.push_back(std::ref(block));
        threadA_mutex.unlock();
        std::this_thread::yield();
    }
}


//*************************************************************************************
//*************************************************************************************
//*************************************************************************************
ThreadB::ThreadB(_tblocks& blocks, _tcrcs_per_block& crcs_per_block, size_t block_count):
    m_blocks(blocks),
    m_crcs_per_block(crcs_per_block),
    m_blk_count(block_count),
    m_cur_block_idx(0)
{

}

//*************************************************************************************
void ThreadB::proccess()
{
    while(m_cur_block_idx<m_blk_count && !m_stop)
    {
        if (m_cur_block_idx==m_blocks.size())
            continue;

        _telement* block = m_blocks[m_cur_block_idx];

        size_t crc32(0);
        for(const auto& elem:*block)
        {
            static const size_t POLY(0x82f63b78);
            crc32 ^= elem;
            for (size_t k = 0; k < 8; k++)
                crc32 = crc32 & 1 ? (crc32 >> 1) ^ POLY : crc32 >> 1;
        }
        threadB_mutex.lock();
        m_crcs_per_block[m_cur_block_idx].push_back(crc32);
        threadB_mutex.unlock();

        ++m_cur_block_idx;
    }
}

