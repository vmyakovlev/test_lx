#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <unordered_map>

class ConfigParser{
private:
    std::string path;
            //key           //val
    std::unordered_map <std::string, std::string> configs;

private:
    bool OptionExists(const std::string &option) const;
    size_t GetNumericValueOption(const std::string &option) const;
    const std::string& GetSringValueOption(const std::string &option) const;
public:
    ConfigParser() = delete;
    ConfigParser (int &argc, char **argv);
    virtual ~ConfigParser(){}

    size_t GetThreadAcount() const {return GetNumericValueOption("-a");}
    size_t GetThreadBcount() const {return GetNumericValueOption("-b");}
    size_t GetBlockCount() const {return GetNumericValueOption("-c");}
    size_t GetBlockSize() const {return GetNumericValueOption("-s");}

};
#endif // CONFIG_PARSER_H
