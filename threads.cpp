
#include <iostream>
#include <random>

#include "threads.h"

//*************************************************************************************
ThreadA::ThreadA(_tblocks& blocks, size_t block_count, size_t size):
    blocks(blocks),
    blk_count(block_count),
    blksize(size)
{

}

//*************************************************************************************
ThreadA::~ThreadA()
{

}

//*************************************************************************************
void ThreadA::proccess()
{
    std::random_device rd;
    std::minstd_rand gen(rd());
    while (blocks.size()<blk_count) {
        _telement* block = new _telement(blksize);

        for(auto& elem: *block)
            elem = gen();

        print_mutex.lock();
        std::cout << "ThreadA#" << std::this_thread::get_id() << " generate" << std::endl;
        print_mutex.unlock();

        add_mutex.lock();
        if (blocks.size()<blk_count)
            blocks.push_back(std::ref(block));
        add_mutex.unlock();
        std::this_thread::yield();
    }
}


//*************************************************************************************
//*************************************************************************************
//*************************************************************************************
ThreadB::ThreadB(_tblocks& blocks, size_t block_count):
    blocks(blocks),
    blk_count(block_count),
    cur_block_idx(0)
{

}

//*************************************************************************************
ThreadB::~ThreadB()
{

}

//*************************************************************************************
void ThreadB::proccess()
{
    while(cur_block_idx<blk_count)
    {
        if (cur_block_idx==blocks.size())
            continue;

        _telement* block = blocks[cur_block_idx];

        std::vector<uint8_t> buff;
        size_t crc32(0);
        for(const auto& elem:*block)
        {
            static const size_t POLY(0x82f63b78);
            crc32 ^= elem;
            for (size_t k = 0; k < 8; k++)
                crc32 = crc32 & 1 ? (crc32 >> 1) ^ POLY : crc32 >> 1;
        }

        print_mutex.lock();
        std::cout << std::dec << "ThreadB#"<<std::this_thread::get_id() << " calc CRC32 for block#"<< cur_block_idx << " = 0x"<<std::hex << crc32 << std::endl;
        print_mutex.unlock();

        ++cur_block_idx;
    }
}

