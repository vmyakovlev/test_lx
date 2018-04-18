#include <iostream>
#include <thread>
#include <mutex>


#include <list>
#include <array>
#include <vector>

#include <random>



#include "config_parser.h"


std::list<std::vector<size_t>> block;


std::vector<std::thread> threadA;
static std::mutex thrA_mut;
void Generate( size_t idx)
{
    std::lock_guard<std::mutex> guard(thrA_mut);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << "Start thread " << idx << ", random=" << gen() << std::endl;

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
        thr = std::thread(&Generate, ++idx);
    }


    for (auto& thr:threadA)
        if(thr.joinable())
            thr.join();


    return 0;
}
