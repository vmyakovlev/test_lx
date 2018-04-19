
#include "config_parser.h"

ConfigParser::ConfigParser (int &argc, char **argv){
    path  = std::string(argv[0]);
    for (int i=1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        configs[arg.substr(0,2)] = arg.substr(2); //TODO
    }
}

//*************************************************************************************
bool ConfigParser::OptionExists(const std::string &option) const{
    return (configs.find(option) != configs.end());
}

//*************************************************************************************
size_t ConfigParser::getNumericValueOption(const std::string &option) const
{
    static const size_t default_value(10);

    const auto opt_itr = configs.find(option);
    if (opt_itr != configs.end())
    {
        try{
            return std::stoi(opt_itr->second);
        }catch(...)
        {
            //return default_value;
        }
    }

    return default_value;
}

//*************************************************************************************
const std::string& ConfigParser::getSringValueOption(const std::string &option) const
{
    static const std::string default_value("");

    auto opt_itr = configs.find(option);
    if (opt_itr != configs.end())
        return opt_itr->second;

    return default_value;
}