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
static std::mutex thrA_mut;

//template <typename Type>


void Generate( size_t block_count, size_t size)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::list<std::vector<uint8_t>> blocks;

    blocks.resize(block_count);
    for(auto& block:blocks)
    {
        block.resize(size);
        for(auto& elem:block)
            elem = gen();
    }

    std::lock_guard<std::mutex> guard(thrA_mut);
    std::cout << "Block[" << block_count << "][" << size << "]:" << std::endl;
    for(const auto block:blocks)
        for(const auto elem:block)
            std::cout << std::showbase << std::hex << std::setw(2) << static_cast<size_t>(elem) << " ";
    std::cout << std::endl;

}

void CalcCRC()
{

}

int main(int argc, char **argv){
    std::cout << "Hello World!" << std::endl;

    ConfigParser config(argc, argv);

    size_t threadA_count = config.GetThreadAcount();
    size_t threadB_count = config.GetThreadBcount();
    size_t block_count = config.GetBlockCount();
    size_t block_size = config.GetBlockSize();
    size_t unknown_int = config.getNumericValueOption("-t");
    std::string unknown_str = config.getSringValueOption("-t");
    size_t unknown_int1 = config.getNumericValueOption("-a");
    std::string unknown_str1 = config.getSringValueOption("-a");
    bool exist1 = config.OptionExists("-t");
    bool exist2 = config.OptionExists("-a");

    threadA.resize(threadA_count);

    for (auto& thr:threadA)
    {
        static size_t idx(0);
        thr = std::thread(&Generate, block_count, block_size);
    }


    for (auto& thr:threadA)
        if(thr.joinable())
            thr.join();


    return 0;
}
