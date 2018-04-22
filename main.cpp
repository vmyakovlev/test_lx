#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <algorithm>
#include <fstream>




#include "typedefs.h"
#include "threads.h"
#include "config_parser.h"







void SaveBlockToFile(size_t block_idx, _telement& block){
    std::ofstream file;
    std::string name = "block" + std::to_string(block_idx) + ".txt";
    file.open (name);
    if ( file.is_open() )
    {
        for (size_t elem_idx(0);elem_idx<block.size();++elem_idx)
        {
            file << std::showbase << std::hex << std::setw(sizeof(block[elem_idx])*2) << static_cast<size_t>(block[elem_idx]) << " ";
            if (elem_idx%8 == 0)
                file <<std::endl;
        }
        file.close();
    }

}

int main(int argc, char **argv){

    _tblocks blocks;
    _tcrcs_per_block crcs_per_block;

    ConfigParser config(argc, argv);

    std::vector<ThreadA*> thrA;
    std::vector<ThreadB*> thrB;

    thrA.resize(config.GetThreadAcount());
    thrB.resize(config.GetThreadBcount());

    for (auto& thr:thrB)
    {
        thr = new ThreadB(blocks, crcs_per_block, config.GetBlockCount());
    }

    for (auto& thr:thrA)
    {
        thr = new ThreadA(blocks, config.GetBlockCount(), config.GetBlockSize());
    }

    for (auto& thr:thrA)
        thr->Wait();
    for (auto& thr:thrB)
        thr->Wait();

    size_t cur_idx(0);
    while (cur_idx<config.GetBlockCount())
    {

        for (auto crcs:crcs_per_block)
        {
            if(crcs.second.size()==config.GetThreadBcount())
            {

                auto first_crc = crcs.second.begin();
                auto compare_crc = std::find_if(++first_crc,crcs.second.end(),[first_crc](size_t _c){return *first_crc!=_c?true:false;});
                if ( compare_crc != crcs.second.end())
                {
                    std::cout << "Mismatch CRCs for block#" << std::dec <<crcs.first <<std::endl;
                     SaveBlockToFile(crcs.first, *blocks[crcs.first]);
                }else
                    std::cout << "Equal CRCs for block#" << std::dec <<crcs.first <<std::endl;

//                crcs_per_block.erase(crcs.first);
                ++cur_idx;

            }
        }

    }




    for(const auto block:blocks)
    {
        static size_t idx(0);
        std::cout << std::dec <<"Block[" << ++idx << "][" << config.GetBlockSize() << "]:" << std::endl;
        for(const auto elem:*block)
            std::cout << std::showbase << std::hex << std::setw(sizeof(elem)*2) << static_cast<size_t>(elem) << " ";
        std::cout << std::endl;
    }

    for (auto& thr:thrA)
        delete thr;
    for (auto& thr:thrB)
        delete thr;

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
