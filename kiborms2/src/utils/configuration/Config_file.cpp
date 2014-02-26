#include "Config_file.h"

boost::regex Config_file::line_regex (LINE_REGEX);

Config_file::Config_file(string const& config_file_name)
{
    load_config_file(config_file_name);
}

Config_file::~Config_file()
{
}

uint32_t Config_file::read_line(string const& line)
{
    boost::cmatch matchs;
    //on gère le cas d'une ligne vide
    if(strlen(line.c_str()) == 0) return SUCCESS;

    //on applique la regex
    if (boost::regex_match(line.c_str(),matchs,line_regex)){
        config_map[matchs[1]] = matchs[2];
        return SUCCESS;
    }

    //si la regex echoue, on
    return FAILURE;
}

uint32_t Config_file::load_config_file(string const& config_file_name)
{
    uint32_t line_num = 1;
    ifstream config_file;
    config_file.open(config_file_name,ios::in);
    if(config_file.is_open()){
        string line = "";

        while(getline(config_file,line)){
            line_num++;
            if(read_line(line)){
                   MSG("Erreur de lecture du fichier de configuration \"%s\", l.%d : \"%s\" ligne incorrecte",config_file_name.c_str(),line_num,line.c_str());
            }
        }
        config_file.close();
        return SUCCESS;
    }else{

        ERR("impossible de charger le fichier de configuration \"%s\"", config_file_name.c_str());
        return FAILURE;
    }
}

void Config_file::print()
{
    MSG("----- configuration file-----");
    for (std::map<string,string>::iterator it= config_map.begin(); it!= config_map.end(); ++it)
        MSG("   %s => %s", (it->first).c_str(), (it->second).c_str());

}


