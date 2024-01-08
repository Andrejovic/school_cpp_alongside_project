//definition of polymorphic element, row and table
// name - Andrej Pribis
// file - poly_table.h

#ifndef POLY_SORT_POLY_TABLE_H
#define POLY_SORT_POLY_TABLE_H

//include
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
//

class abstract_element;
using valptr = std::unique_ptr<abstract_element>;

//implementation of abstract_element
class abstract_element{
public:
    virtual valptr clone() = 0;
    virtual void print(std::ostream& f) = 0;
    virtual bool operator<(const abstract_element& rhs) const = 0;
    virtual bool operator>(const abstract_element& rhs) const = 0;
};

//implementation of element
template<typename T>
class element : public abstract_element{
public:
    explicit element( T x) : x_(x) {};
    virtual valptr clone() override;
    void print(std::ostream& f) override;
    bool operator>(const abstract_element& rhs) const override;
    bool operator<(const abstract_element& rhs) const override;
    T x_;
};

//########################## templated methods of element ####################################
template<typename T>
bool element<T>::operator<(const abstract_element &rhs) const {
    return this->x_ < static_cast<const element<T>&>(rhs).x_;
}

template<typename T>
bool element<T>::operator>(const abstract_element &rhs) const {
    return this->x_ > static_cast<const element<T>&>(rhs).x_;
}

template<typename T>
void element<T>::print(std::ostream& f) {
    f << x_;
}

template<typename T>
valptr element<T>::clone() {
    return std::make_unique<element<T>>(*this);
}

//implementation of poly_row - object that contains vector<unique_ptr<element>>
class poly_row {
public:
    poly_row( const std::vector<std::string>& sorters) : sorters(sorters) {};
    poly_row( const poly_row& r) : sorters(r.sorters) { clone(r); };
    void add( valptr p);
    void print(std::ostream& f, char separator);
    poly_row& operator=(const poly_row& );
    template<typename T> T& operator[](const size_t& i);
    std::vector<valptr> row;
    std::vector<std::string> sorters;
private:
    void clone( const poly_row& r);
};

//##################################### comparison functor ###########################################################
struct poly_table_compare {
    bool operator()(const std::unique_ptr<poly_row> &left,const std::unique_ptr<poly_row> &right) const {
        std::vector<std::string> sorters = left->sorters;
        for (std::string& x : sorters) {
            int col = x[1] - '0';
            if(*(left->row[col - 1]) < *(right->row[col - 1])){
                return true;
            }
            else if( *(left->row[col - 1]) > *(right->row[col - 1])){
                return false;
            }
        }
        return false;
    }
};

//implementation of poly_table - object that contains multiset<unique_ptr<poly_row>>
class poly_table {
public:
    poly_table(){};
    void add_row(const poly_row& r);
    void print(std::ostream& f, char separator);
    std::map<int,char> map_sorters;

private:
    std::multiset<std::unique_ptr<poly_row>,poly_table_compare> table;
};

#endif //POLY_SORT_POLY_TABLE_H