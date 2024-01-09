#include <iostream>

#include "StretchyArray.h"
#include <string>
#include <stdexcept>

using namespace std;



int main() {
    try{
        Pole<int> arr(10);

        for (int i = 0; i< 55; ++i)
        {
            arr.push_back(i);
        }

        for (const auto& element : arr){
            cout << element << "\n";
        }
        cout << "end of auto for loop" << "\n";

        for ( auto&& i = arr.begin(); i != arr.end(); ++i){
            ++i;
            cout << *i << "\n";
        }
        cout << "end of begin-end for loop" << "\n";



        //cout << arr[55];

        cout << arr.at(5) << " at 5\n";
        //cout << arr.at(55) << " at 55\n";
    }
    catch(at_err(&e)){
        cerr << e.what() << "\n";
        cerr << e.getIndex();
    }
    catch(end_err(&e)){
        cerr << e.what() << "\n";
        cerr << "size of container at time of error: " << e.getSize();
    }
}
