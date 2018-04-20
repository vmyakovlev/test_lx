#include <iostream>
#include <unistd.h>
#include <iomanip>





#include "typedefs.h"
#include "threads.h"
#include "config_parser.h"


std::vector<ThreadA*> thrA;
std::vector<ThreadB*> thrB;


static _tblocks blocks;



int main(int argc, char **argv){

    ConfigParser config(argc, argv);


    thrA.resize(config.GetThreadAcount());
    thrB.resize(config.GetThreadBcount());

    for (auto& thr:thrB)
    {
        thr = new ThreadB(blocks, config.GetBlockCount());
    }

    for (auto& thr:thrA)
    {
        thr = new ThreadA(blocks, config.GetBlockCount(), config.GetBlockSize());
    }


    for (auto& thr:thrA)
    {
        delete thr;
    }
    for (auto& thr:thrB)
    {
        delete thr;
    }
  //  ThreadA thrA = new ThreadA(&blocks, config.GetBlockCount(), config.GetBlockSize());


//    for (auto& thr:threadA)
//        if(thr.joinable())
//            thr.join();

//    for (auto& thr:threadB)
//        if(thr.joinable())
//            thr.join();

    for(const auto block:blocks)
    {
        static size_t idx(0);
        std::cout << std::dec <<"Block[" << ++idx << "][" << config.GetBlockSize() << "]:" << std::endl;
        for(const auto elem:*block)
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
