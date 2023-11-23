#include "Senzam.h"
#include <iostream>

void Senzam::add(Valptr p) {
    pole_.push_back( move( p));
}

void Senzam::print() {
    for(auto&& x : pole_)
        x->print();
}

void Senzam::clone(const Senzam &s) {
    for( auto&& x: s.pole_) pole_.push_back( x->clone());
}

Senzam::Senzam(const Senzam &s) {
    clone(s);
}

Senzam& Senzam::operator=(const Senzam &s) {
    if (this == &s)
        return *this;
    pole_.clear(); clone(s); return *this;
}

void StringVal::print() {
    std::cout << x_ << '\n';
}

Valptr StringVal::clone() {
    return std::make_unique<StringVal>(*this);
}

void IntVal::print() {
    std::cout << x_ << '\n';
}

Valptr IntVal::clone() {
    return std::make_unique<IntVal>(*this);
}