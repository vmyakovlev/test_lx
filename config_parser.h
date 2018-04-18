#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <map>

class ConfigParser{
private:
    std::string path;
            //key           //val
    std::map <std::string, std::string> configs;
public:
    ConfigParser() = delete;
    ConfigParser (int &argc, char **argv);
    virtual ~ConfigParser(){}


    inline size_t GetThreadAcount() const {return getNumericValueOption("-a");}
    inline size_t GetThreadBcount() const {return getNumericValueOption("-b");}
    inline size_t GetBlockCount() const {return getNumericValueOption("-c");}
    inline size_t GetBlockSize() const {return getNumericValueOption("-s");}

    bool OptionExists(const std::string &option) const;
    size_t getNumericValueOption(const std::string &option) const;
    const std::string& getSringValueOption(const std::string &option) const;
};
#endif // CONFIG_PARSER_H
