#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//slovo je string ktory zacina a konci medzerou

//veta je pole stringov ktore konci bodkou a medzerou

//pocet radek je urceny poctom /n

//pocitame /n ako znak?

//treba oddelit vsetky cisla a tie samostatne spocitat

int reading_from_stream( istream& s)
{
    char c;
    string word;
    int c_count = 0;
    int w_count = 0;
    int r_count = 0;
    for(;;) {
        c = s.get();
        if (c == ' '){
            w_count++;
        }
        else if (c == '\n'){
            r_count++;
        }
        if (s.fail())
            return c_count;
        else
            c_count++;
    }
}

int main() {
    int char_count = 0;
    char_count+=reading_from_stream(cin);

    ifstream f;
    f.open("file.txt");
    char_count+=reading_from_stream(f);

    std::cout << char_count << std::endl;

}
