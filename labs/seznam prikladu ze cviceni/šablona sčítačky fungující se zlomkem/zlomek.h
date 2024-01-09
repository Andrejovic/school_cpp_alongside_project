#ifndef TEMPLATING_ZLOMEK_H
#define TEMPLATING_ZLOMEK_H
#include <vector>
#include <iostream>

template<typename T> class zlomek {
public:
    zlomek(T i1=0, T i2=0) : numerator(i1), denuminator(i2) {}
    template<typename X>
    friend zlomek<X> operator+ (const zlomek<X>&x,const zlomek<X>&y);

    template<typename Y>
    friend zlomek<Y> operator- (const zlomek<Y>&x,const zlomek<Y>&y);
    std::vector<T> result() { return {numerator, denuminator}; }
    void print_to_cout() {
        std::cout << numerator << "/" << denuminator << "\n";
        return;
    }
private:
    T numerator;
    T denuminator;
};

template <typename X>
zlomek<X> operator+ (const zlomek<X>&x,const zlomek<X>&y){
    if (x.denuminator == y.denuminator){
        return zlomek<X>{y.numerator + x.numerator,x.denuminator};
    }
    return zlomek<X>{(y.numerator * x.denuminator) + (x.numerator * y.denuminator), x.denuminator * y.denuminator};
}

template <typename Y>
zlomek<Y> operator- (const zlomek<Y>&x, const zlomek<Y>&y){
    if (x.denuminator == y.denuminator){
        return zlomek<Y>{x.numerator - y.numerator, x.denuminator};
    }
    return zlomek<Y>{(x.numerator * y.denuminator) - (y.numerator * x.denuminator), x.denuminator * y.denuminator};
}

template <typename W> class DA{
    public:
        DA( W val=0) : v_(val) {};
        template<typename A>
        friend DA<A> operator+
        (const DA<A>&x, const DA<A>& y);
        void print_to_cout(){
            v_.print_to_cout();
        }
    private:
        W v_;
    };

template <typename A>
DA<A> operator+( const DA<A>&x, const DA<A>&y){
    return DA<A> (x.v_ + x.v_ + y.v_ + y.v_);
}

#endif //TEMPLATING_ZLOMEK_H
