#include <iostream>
#include "zlomek.h"

int main() {
    zlomek<unsigned long> a(2, 5),b(5, 5);
    zlomek<unsigned long> c,d;
    c = a + b;
    c.print_to_cout();
    d = b - a;
    d.print_to_cout();
    c = a + a + a + a + a + b;
    c.print_to_cout();

    DA<zlomek<unsigned long>> e(5);
    e = e + e;
    e.print_to_cout();




    return 0;
}
