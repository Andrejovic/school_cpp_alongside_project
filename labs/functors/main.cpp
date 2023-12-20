#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct funktor1{
public:
    funktor1(int n) : n(n){};
    bool operator() (int i){
        bool result = false;
        if(first)
            first = false;
        else
            result = abs(prev - i) >= n;
        prev = i;
        return result;
    }
private:
    int n;
    int prev;
    bool first = true;
};

int main() {
    //task 1
    vector<int> vec = {1, 5, 8, 10, 6};
    vector<int> result;
    int x = 3;
    int y = 4;

    for_each(vec.cbegin(),vec.cend(), [&result, &x, &y](int i){if(i > x) result.emplace_back(i+y);});
    for (auto&& item : result){
        std::cout << item << "\n";
    }
    cout << "done task 1 \n";

    int distance = 2;
    auto it = find_if(vec.cbegin(), vec.cend(), funktor1(distance));
    if (it == vec.cend()){
        cout << "NONE";
    }
    else {
        cout << *it;
    }
    //
    return 0;
}
