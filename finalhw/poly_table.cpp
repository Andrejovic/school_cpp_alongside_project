//implementation of poly_table.h
// name - Andrej Pribis
// file - poly_table.cpp

//include
#include "poly_table.h"
#include <utility>
using std::endl;
//



//######################################## implementation of poly_row methods#########################################
void poly_row::add(valptr p) {
    row.push_back( std::move(p));
}

void poly_row::clone(const poly_row &r) {
    for( auto && x: r.row) {
        row.push_back( x->clone());
    }

}

void poly_row::print(std::ostream& f, char separator) {
    for(size_t i = 0; i < row.size(); i++){
        row[i]->print(f);
        if(i == row.size()-1)
            break;
        f << separator;
    }
}

poly_row& poly_row::operator=(const poly_row &r) {
    if (this == &r)
        return *this;
    row.clear();
    clone(r);
    return *this;
}

template<typename T>
T& poly_row::operator[](const size_t &i) {
    return row[i];
}



//###################### poly_table method implementations ##################################

void poly_table::add_row(const poly_row& r) {
    table.insert(std::make_unique<poly_row>(r));
}

void poly_table::print(std::ostream &f,char separator) {
    size_t i = 0;
    for (auto&& it : table){
        it->print(f,separator);

        if (i == table.size() - 1){
            break;
        }
        i++;
        f << endl;
    }
}

/*
poly_row& poly_table::operator[](size_t i) {
    return *table[i];
}
*/

//discarted function for checking if all rows are equal length

/*bool poly_table::equal_rows() {
    for(size_t i = 1; i<table.size(); i++)
        if(table[i]->length() != table[0]->length()){
            std::cerr << "row: "<< i+1 <<" has non-equal length" << endl << "NEPRIPUSTNY FORMAT";
            exit(0);
        }
    return true;
}*/