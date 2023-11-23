
#include "operations.h"
#include <set>
#include <cctype>

using namespace std;

string to_lower(string s){
    for (char& ch : s){
        ch = tolower(ch);
    }
    return s;
}

bool my_sort::operator()(const std::string& s1, const std::string& s2) const {
    return s1.size() < s2.size() || s2.size() >= s1.size() && s1 < s2;
}

bool my_sort_map::operator()(const std::string &s1, const std::string &s2) const {
    string s1_low = to_lower(s1);
    string s2_low = to_lower(s2);
    if (s1_low == s2_low){
        return s2 < s1;
    }
    return s1_low < s2_low;
}

void operations::add(const string& word, const string& foreign ) {
    auto it = mapa_slovniku.find(word);
    if (it != mapa_slovniku.end()){
        mapa_slovniku[word].emplace(foreign);
    }
    else{
        my_set begin {foreign};
        mapa_slovniku.emplace(pair(word,begin));
    }
}

void operations::del(const std::string& word, const std::string& foreign) {
    if (mapa_slovniku.find(word) != mapa_slovniku.cend()){
        if (!foreign.empty()){
            my_set *jesus = &mapa_slovniku[word];
            jesus->erase(foreign);
        }
        else {
            mapa_slovniku.erase(word);
        }
    }
}

my_set operations::find(const string& word) {
    my_set slovo = mapa_slovniku[word];
    if (mapa_slovniku.find(word) != mapa_slovniku.cend()){
        return mapa_slovniku[word];
    }
    else {
        my_set wrong = {"WRONG WORD"};
        return wrong;
    }
}

map<string, my_set, my_sort_map> operations::prefix(const string& word) {
    string lower = "";
    string upper = "";
    int i = 0;
    for( char x : word){ //the lower version of the prefix would be before the upper one
        i++; // i dont like this myself but i dont know of other way to do it without going through the entire map(dictionary)
        char y = tolower(x);
        if (i != word.length()) {
            lower += y;
            upper += x;
        }
        else{
            lower += --y;
            upper += ++x;
        }
    }

    auto prefixed_begin = mapa_slovniku.lower_bound(lower); //i am open to better ideas for this
    auto prefixed_end = mapa_slovniku.upper_bound(upper);
    return map<string, my_set, my_sort_map>(prefixed_begin, --prefixed_end);
}
