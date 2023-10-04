#include <iostream>
#include <vector>
using namespace std;

int zpracuj(char * arg)
{
    int argI = atoi(arg);
    for (int j = 1; j < 11; j++) 
    {
        std::cout << argI;
        std::cout << "*";
        std::cout << j;
        std::cout << "=";
        std::cout << argI * j << std::endl;
    }
    
    return 0;
}

int main( int argc , char ** argv )
{
    vector<string> arg( argv, argv+argc);
    for (int i = 1; i < argc; i++)
    {
        zpracuj(argv[i]);
    }
}
