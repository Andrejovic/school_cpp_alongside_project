//implementation of methods in sorter.h used to go through input
// name - Andrej Pribis
// file - sorter.cpp

//include
#include "sorter.h"
#include <algorithm>
//

using namespace std;



parameters sorter::get_parameters(int argc, char **argv) {
    string input = const_default_input;
    string output = const_default_output;
    string separator = " "; // not casting separator to char instantly so i can use sorter::find without template

    vector<string> sorters = {};

    int i = 1;
    while (i < argc){
        string arg = argv[i];

        if (arg.find("-i") != string::npos){
            string next = argv[i+1]; //sorters arent defaulted so always at least one more
            input = this->find(arg,"-i",next,i);
        }
        else if(arg.find("-o") != string::npos) {
            string next = argv[i+1];
            output = this->find(arg,"-o",next,i);
        }
        else if(arg.find("-s") != string::npos) {
            string next = argv[i+1];
            separator = this->find(arg,"-s",next,i);
        }
        else{
            sorters.emplace_back(argv[i]);
        }
        i++;
    }
    parameters par(input,output,separator, sorters);
    return par;
}

string sorter::find(const string &argument, const string &type, const string &next, int& iterator) {
    if (argument == type){
        iterator++;
        return next;
    }
    return argument.substr(2);
}

void convert_sorters_to_map(const vector<string>& sorters, poly_table& unsorted_t){
    map<int,char> m_sort;
    for(auto sorter : sorters){
        if (sorter.length() > 1) {
            int col_id = stoi(sorter.substr(1));
            char type = sorter[0];
            m_sort.emplace(col_id, type);
        }
        else{
            std::cerr << "Invalid sorter: " << sorter;
            exit(0);
        }
    }
    unsorted_t.map_sorters = m_sort;
}


poly_table sorter::read(istream &s, char separator, const vector<string>& sorters) {
    poly_table unsorted_t;

    string row; //isn't good to put everything to string

    int line_num = 0;

    convert_sorters_to_map(sorters,unsorted_t);

    for(;;){
        poly_row r(sorters);
        getline(s, row);
        if (s.fail()){
            //if (unsorted_t.equal_rows()){
            return unsorted_t;

        }
        line_num++;
        process_row(row, separator, unsorted_t.map_sorters, line_num, r);
        unsorted_t.add_row(r);
    }
}

void sorter::process_row(const std::string& row, char separator, const map<int,char>& map_sorters, int line_num, poly_row& r) {
    stringstream srow(row);
    string word;
    int i = 1;
    try { //i don't like this nesting
        while (getline(srow, word, separator)) {
            if (map_sorters.find(i) != map_sorters.cend()) {
                switch (map_sorters.at(i)) { //would love to put the if into this switch but cant figure out what at does on failure
                    case 'N': {              //and i have a feeling it makes an error which has to be done with try and doesnt fix the nesting
                        int add = stoi(word);
                        r.add(make_unique<element<int>>(add));
                        i++;
                        continue;
                    }
                    case 'S': {
                        r.add(make_unique<element<std::string>>(word));
                        i++;
                        continue;
                    } // easily expendable
                }
            }
            r.add(make_unique<element<std::string>>(word));
            i++;
        }
        if (row[row.length() - 1] == separator){
            r.add(make_unique<element<std::string>>(""));
        }
    }
    catch(exception &err){
        cerr << "error at column: " << i << " and row: " << line_num << endl << "NEPRIPUSTNY FORMAT";
        exit(0);
    }
}