#include <iostream>
#include <string.h>
using namespace std;

const int DEFAULT_FROM = 1; //default constant values for from and to
const int DEFAULT_TO = 10;

class Class {
public:
    void zpracuj_argumenty(int argc, char ** arg){
        int ignore = 1; //automatically ignore the first argument
        int from = DEFAULT_FROM;
        int to = DEFAULT_TO;
        for (int i = 1; i < argc; i++){ //same here
            if (strcmp("-f" , arg[i]) == 0){ // == didn't work, don't know why, couldn't get compare to work, that's why i'm using this
                i++;
                from = stoi(arg[i]);
                ignore+=2; //ignore two more arguments (one parameter and one argument)
            }
            if (strcmp("-t" , arg[i]) == 0){
                i++;
                to = stoi(arg[i]);
                ignore+=2;
            }
        }
        nasobilka(arg, argc, from, to, ignore);
    }
private:
    void nasobilka(char ** arg, int argc, int from, int to, int ignore)
    {
        for (int i = ignore; i < argc; i++){
            int argI = stoi(arg[i]);
            for (int j = from; j < to+1; j++){
                std::cout << argI << "*" << j << "=" << argI * j << std::endl;
            }
        }
    }
};

int main( int argc , char ** argv ){
    Class nasobit;
    nasobit.zpracuj_argumenty(argc,argv);
}

