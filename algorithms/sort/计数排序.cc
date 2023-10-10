#include <iostream>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <array>
using namespace std;

int main() {
    array<int, 1000> student_grades;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{100, 20};

    // 值最可能接近平均
    // 标准差影响生成的值距离平均数的分散
 
    std::map<int, int> hist{};

    for(int n=0; n < 10000; ++n) {
        ++hist[std::round(d(gen))];
    }

    for(auto p : hist) {
        std::cout << std::setw(2) << p.first << ' ' << std::string(p.second/20, '*') << '\n';
    }
    for(int i = 0; i < 1000; i++) {

    }
}
