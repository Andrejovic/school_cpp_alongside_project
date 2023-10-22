#include <iostream>
#include <string>
#include "counter.h"

void reading_from_stream( std::istream& s)
{
    char c;
    std::string word;
    for(;;) {
        c = s.get();
        if (s.fail())
            return;
    }
}