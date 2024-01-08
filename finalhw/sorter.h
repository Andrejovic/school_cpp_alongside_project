//definition of sorter class and its method
// name - Andrej Pribis
// file - sorter.h

#ifndef POLY_SORT_SORTER_H
#define POLY_SORT_SORTER_H

//include
#include <fstream>
#include <sstream>
#include "poly_table.h"
//

//konstanty
const std::string const_default_input = "__DEFAULT_INPUT__";
const std::string const_default_output = "__DEFAULT_OUTPUT__";
//

//an object that holds all information about arguments/parameters
struct parameters{
    parameters(std::string& in, std::string& out, std::string& sep, std::vector<std::string>& sor) : in(in),out(out),sep(sep[0]),sor(sor) {};
    std::string in;
    std::string out;
    char sep;
    std::vector<std::string> sor;
};

//sorter class, only for encapsulation of methods
class sorter {
public:
    parameters get_parameters(int argc, char** argv);
    std::string find(const std::string& argument,const std::string& type, const std::string& next, int& iterator);

    poly_table read(std::istream &s,char separator,const std::vector<std::string>& sorters);
    void process_row(const std::string& row, char separator, const std::map<int,char>& sorters, int line_num, poly_row& r);
};


#endif //POLY_SORT_SORTER_H