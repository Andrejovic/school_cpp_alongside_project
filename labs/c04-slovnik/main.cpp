#include <iostream>
#include "operations.h"
using namespace std;

using my_set = set<string , my_sort> ;

int main() {
    operations slovnik;

    slovnik.add("slovo","word");
    slovnik.add("slovo","slur");
    slovnik.add("slovo","jezis");
    slovnik.add("slovo", "non");
    slovnik.add("slovox", "non");
    slovnik.add("slovoxy", "non");
    slovnik.add("slovoxy", "slur");
    slovnik.del("slovo","slur");
    slovnik.add("slov","wor");
    slovnik.add("Slov","Word");
    slovnik.add("Slovo","Wordy");
    slovnik.add("slovp","idk");
    slovnik.add("xrays","roetgen");
    my_set foreign = slovnik.find("slovo");

    map<string, my_set, my_sort_map> prefix_check = slovnik.prefix("slovo");

    for (string const& fore : foreign){
        cout << fore << ", ";
    }
}
