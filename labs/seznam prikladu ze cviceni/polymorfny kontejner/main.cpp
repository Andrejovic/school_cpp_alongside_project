#include <iostream>
#include "Senzam.h"

using namespace std;

int main() {
    Senzam s1,s2;
    s1.add( make_unique<IntVal>(123));
    s1.add( make_unique<StringVal>("456"));
    s1 = s1;
    s1.print();
}
