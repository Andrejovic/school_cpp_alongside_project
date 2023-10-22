#include <iostream>
#include <string>
#include <fstream>
#include "counter.h"
using namespace std;

//slovo je string ktory zacina a konci medzerou

//veta je pole stringov ktore konci bodkou a medzerou

//pocet radek je urceny poctom /n

//pocitame /n ako znak?

//treba oddelit vsetky cisla a tie samostatne spocitat



int main() {
    counter my_c;
    my_c.reading_from_stream(cin);

    ifstream f;
    f.open("file.txt");
    my_c.reading_from_stream(f);

    //std::cout << char_count << std::endl;

}
