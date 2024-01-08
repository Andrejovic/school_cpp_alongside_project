#include <iostream>

#include "StretchyArray.h"
#include <string>

using namespace std;

int main() {
    Pole<int> arr(10);

    for (int i = 0; i< 55; ++i)
    {
        arr.push_back(i);
    }

    for (const auto& element : arr){
        cout << element << "\n";
    }

    /*for ( auto&& i = arr.begin(); i != arr.end(); ++i){
        cout << *i << "\n";
    }*/
}
