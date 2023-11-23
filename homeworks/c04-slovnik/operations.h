#ifndef SLOVNIK_OPERATIONS_H
#define SLOVNIK_OPERATIONS_H

#include <map>
#include <string>
#include <vector>
#include <set>

struct my_sort{ // i dont know if having sort implementation is okay for the class in which header im in
    bool operator()( const std::string& s1, const std::string& s2) const;
};

struct my_sort_map{ // same as before, only reason why i have only one header for a class and two functors
    bool operator()( const std::string& s1, const std::string& s2) const;
};

using my_set = std::set<std::string , my_sort> ;

class operations {
public:
    void add(const std::string& word, const std::string& foreign);
    void del(const std::string& word, const std::string& foreign = "");
    my_set find(const std::string& word);
    std::map<std::string, my_set, my_sort_map> prefix(const std::string& word);

private:
    std::map<std::string, my_set, my_sort_map> mapa_slovniku;
};

#endif
