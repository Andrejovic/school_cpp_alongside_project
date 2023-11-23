#ifndef LAB22_11_SENZAM_H
#define LAB22_11_SENZAM_H

#include "AbstractVal.h"
#include <memory>
#include <vector>
#include <string>
class AbstractVal;
using Valptr = std::unique_ptr<AbstractVal>;

class AbstractVal {

public:
    virtual void print() = 0;
    virtual Valptr clone() = 0;
};



class IntVal: public AbstractVal{
public:
    explicit IntVal( int x) : x_( x) {};
    virtual void print() override;
    virtual Valptr clone() override;
private:
    int x_;
};

class StringVal: public AbstractVal{
public:
    StringVal( std::string x) : x_( x) {};
    virtual void print() override;
    virtual Valptr clone() override;
private:
    std::string x_;
};



class Senzam {
public:
    Senzam() {}
    Senzam( const Senzam& s);
    Senzam& operator=( const Senzam& s);
    void add( Valptr p);
    void print();
private:
    std::vector<Valptr> pole_;
    void clone( const Senzam& s);
};


#endif //LAB22_11_SENZAM_H
