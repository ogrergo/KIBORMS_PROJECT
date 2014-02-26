#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <string>
#include <map>
#include <fstream>
#include <stdint-gcc.h>
#include <boost/regex.hpp>
#include "utils/macro/debug_macro.h"

#define NO_VALUE ""
#define LINE_REGEX "\\s*([^=\\s]+)\\s*=\\s*\"([^\"]*)\"\\s*"

#define DEFAULT_CONFIG_FILE "data/config/default.cfg"

using namespace std;

class Config_file
{
    public:
        Config_file(string const& config_file_name = DEFAULT_CONFIG_FILE);
        virtual ~Config_file();

        uint32_t load_config_file(string const& config_file_name);

        void print();

        string operator[] (string const& key){

            map<string,string>::iterator it = config_map.find(key);
            if (it != config_map.end()){
                return it->second;
            }else{
                return NO_VALUE;
            }
        }
    protected:
    private:
        uint32_t read_line(string const& line);

        map<string,string> config_map;
        static boost::regex line_regex ;

};

#endif // CONFIG_FILE_H
