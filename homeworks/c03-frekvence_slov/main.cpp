#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

void print(const map<string,int> &mapa){
    for (auto&& [word,count] : mapa){
        cout << word << ":" << count << endl;
    }
}

void myparse(const string &s, map<string,int> &mapa){
    if(mapa.find(s)!=mapa.end()){
        mapa[s]++;
    }
    else{
        mapa.insert(pair{ s,1});
    }
}

void read(istream& f){
    map<string,int> mapa;
    string s;
    for(;;){
        f >> s;
        if (f.fail()){
            print(mapa);
            return;
        }
        s[0]=tolower(s[0]); //works for only first letters not for WORDS or esoteric wOrDs
        myparse(s, mapa);
    }
}

int main( int argc, char** argv) {
    if (argc>1){
        ifstream f;
        f.open(argv[1]);
        read(f);
    }
    else{
        read(cin);
    }


    return 0;
}
