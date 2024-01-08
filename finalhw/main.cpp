//main function to start the program and do basic in/output handling
// name - Andrej Pribis
// file - main.cpp

//include
#include "sorter.h"
//

using namespace std;

int main(int argc, char** argv) {
    sorter sort;
    parameters par = sort.get_parameters(argc, argv);
    poly_table output;

    //input handling

    if(par.in == const_default_input){
        output = sort.read(cin, par.sep, par.sor);
    }
    else{
        ifstream in(par.in);
        output = sort.read(in, par.sep, par.sor);
        in.close();
    }

    //output handling
    if(par.out == const_default_output){
        output.print(std::cout,par.sep);
    }
    else{
        ofstream out(par.out);
        output.print(out,par.sep);
        out.close();
    }

    return 0;
}