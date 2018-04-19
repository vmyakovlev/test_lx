#include <iostream>
#include <unistd.h>
#include <iomanip>

#include <thread>
#include <mutex>


#include <list>
#include <array>
#include <vector>

#include <random>



#include "config_parser.h"





std::vector<std::thread> threadA;
std::vector<std::thread> threadB;
std::mutex mutex_add;


//template <typename Type>

static std::list<std::vector<uint8_t>> blocks;
static std::list<std::vector<uint8_t>> blocks;


void Generate(size_t id,  size_t block_count, size_t size)
{
    std::random_device rd;
    std::minstd_rand gen(rd());
    while (blocks.size()<block_count) {
        if (!mutex_add.try_lock())
            continue;
        blocks.push_back(std::vector<uint8_t>(size));
        mutex_add.unlock();

        //auto& data = blocks.back();//end();

        for(auto& elem: blocks.back())
            elem = gen();

        std::this_thread::yield();
    }
}

void CalcCRC(size_t id,  size_t block_count, size_t size)
{
static const POLY(0x82f63b78);

/* CRC-32 (Ethernet, ZIP, etc.) polynomial in reversed bit order. */
/* #define POLY 0xedb88320 */
    std::vector<uint8_t> buff;
    size_t crc32(0);
    for(const auto& elem:buff)
    {
        crc32 ^= elem;
        for (k = 0; k < 8; k++)
            crc32 = crc32 & 1 ? (crc32 >> 1) ^ POLY : crc32 >> 1;
    }
//while (len--) {
//        crc ^= *buf++;
//        for (k = 0; k < 8; k++)
//            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
//    }

//uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len)
//{
//    int k;

//    crc = ~crc;
//    while (len--) {
//        crc ^= *buf++;
//        for (k = 0; k < 8; k++)
//            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
//    }
//    return ~crc;
//}
}

int main(int argc, char **argv){
    std::cout << "Hello World!" << std::endl;

    ConfigParser config(argc, argv);

    threadA.resize(config.GetThreadAcount());
    threadB.resize(config.GetThreadBcount());

    for (auto& thr:threadA)
    {
        static size_t idx(0);
        thr = std::thread(&Generate, ++idx, config.GetBlockCount(), config.GetBlockSize());
    }
    for (auto& thr:threadB)
    {
        static size_t idx(0);
        thr = std::thread(&CalcCRC, ++idx, config.GetBlockCount(), config.GetBlockSize());
    }



    for (auto& thr:threadA)
        if(thr.joinable())
            thr.join();

    for (auto& thr:threadB)
        if(thr.joinable())
            thr.join();

    for(const auto block:blocks)
    {
        static size_t idx(0);
        std::cout << std::dec <<"Block[" << ++idx << "][" << config.GetBlockSize() << "]:" << std::endl;
        for(const auto elem:block)
            std::cout << std::showbase << std::hex << std::setw(2) << static_cast<size_t>(elem) << " ";
        std::cout << std::endl;
    }
    return 0;
}


//    size_t threadA_count = config.GetThreadAcount();
//    size_t threadB_count = config.GetThreadBcount();
//    size_t block_count = config.GetBlockCount();
//    size_t block_size = config.GetBlockSize();
//    size_t unknown_int = config.getNumericValueOption("-t");
//    std::string unknown_str = config.getSringValueOption("-t");
//    size_t unknown_int1 = config.getNumericValueOption("-a");
//    std::string unknown_str1 = config.getSringValueOption("-a");
//    bool exist1 = config.OptionExists("-t");
//    bool exist2 = config.OptionExists("-a");
