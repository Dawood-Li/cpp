#include <bits/stdc++.h>

using namespace std;

auto adder = [] (int sum) {
    auto f = [] (int& sum, int num) -> int {
        sum += num;
        return sum;
    };
    return bind(f, sum, placeholders::_1);
};


int main() {
    auto f = adder(0);
    cout << f(1) << "\n";
    cout << f(2) << "\n";
    cout << f(3) << "\n";
}
