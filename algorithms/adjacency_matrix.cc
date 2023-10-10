// File: adjacency_matrix.cc
// Date: 20230730
// Author: dawood
// Email: dawood_li@outlook.com
// Description: 邻接矩阵相关算法实现
//              包含 dijkstra 和 floyd, 
//              将结果交叉校验 已通过
// Inspired by: https://www.bilibili.com/video/BV1q4411M7r9
// License: None

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits> // for INT_MAX

#include <sstream> // for load_matrix_from_file
#include <random> // for random
#include <algorithm> // for reverse
using namespace std;

/// @brief 随机生成邻接矩阵（必然是方形）
/// @param sz 矩阵尺寸
/// @return 邻接矩阵
vector<vector<int>>
randomly_generated_adjacency_matrix (
    int sz
) {  
    auto matrix = vector<vector<int>>(sz, vector<int>(sz, 0));    
    auto gen    = mt19937 { random_device {} () };
    auto dis    = uniform_int_distribution<> { 0, sz * 2 };

    for (int i = 0; i < sz; i++)
    for (int j = 0; j < sz; j++) {
        if (i == j) {
            matrix[i][j] = INT_MAX;
        } else {
            int rand = dis(gen);
            matrix[i][j] = rand < sz ? rand : INT_MAX;
        }
    }

    return matrix;
}

/// @brief 显示矩阵
/// @param matrix 矩阵
void
print_matrix (
    const vector<vector<int>>& matrix
) {
    for (auto& row : matrix) {
        for (auto &col : row) {
            if (col == INT_MAX) {
                cout << "∞" << ' ';
            } else {
                cout << col << ' ';
            }
        } cout << '\n';
    }
}

/// @brief 保存矩阵
/// @param matrix 矩阵
/// @param filename 文件路径
void
save_matrix_to_file (
    const vector<vector<int>>& matrix,
    const string& filename
) {
    auto file = ofstream(filename);
    for (auto& row : matrix) {
        for (auto &col : row) {
            file << col << ' ';
        } file << '\n';
    }
}
/// @brief 从文件加载矩阵
/// @param filename 文件路径
/// @return 矩阵
vector<vector<int>>
load_matrix_from_file (
    const string& filename
) {
    ifstream file(filename);
    vector<vector<int>> matrix;
    string line;
    int num;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        while (iss >> num) { row.push_back(num); }
        matrix.push_back(row);
    }

    return matrix;
}

/// @brief 计算所有路径的最短路径
/// @param matrix 邻接矩阵 
/// @return 结果矩阵
vector<vector<int>>
floyd_solution (
    const vector<vector<int>>& matrix
) {
    // initialization
    const auto n = matrix.size();
    auto dist = matrix;
    auto seq  = vector<vector<int>>(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            seq[i][j] = i == j ? -1 : j;
        }   
    }

    // core algorithm
    for (size_t k = 0; k < n; k++) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX &&
                    dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]
                ) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    seq[i][j] = seq[i][k];
                }
            }
        }
    }

    return seq;
}

/// @brief 从floyd结果矩阵中提取最短路径
/// @param matrix 结果矩阵
/// @param start 起点
/// @param end 终点
/// @return 路径
vector<int>
floyd_getpath (
    const vector<vector<int>>& matrix,
    int start,
    int end
) {
    vector<int> path;
    for (int current = start; current != end; current = matrix[current][end]) {
        path.push_back(current);
    } path.push_back(end);
    return path;
}

vector<int>
dijkstra_solution (
    const vector<vector<int>>& m,
    int start
) {
    const int n = m.size();
    std::vector<int> visited;
    std::vector<int> dist;
    std::vector<int> parent;

    // 更新一个新的点，收敛各点权值
    auto update = [&] (int p) {
        visited[p] = true;
        for(int i = 0; i < n; i++) {
            if(m[p][i] != INT_MAX) {
                if(dist[p] + m[p][i] < dist[i]) {
                    dist[i] = dist[p] + m[p][i];
                    parent[i] = p;
                }
            }
        }
    };

    // 初始化
    visited = std::vector<int>(n, false);
    dist    = std::vector<int>(n, INT_MAX);
    parent  = std::vector<int>(n, -1);
    dist[start] = start;
    update(start);

    // 循环求解
    while(1) {

        int min = -1;
        int min_dis = INT_MAX;

        for(int i = 0; i < n; i++) {
            if(visited[i] == false) {
                if(dist[i] < min_dis) {
                    min = i;
                    min_dis = dist[i];
                }
            }
        }
        
        if(min_dis == INT_MAX) {
            break;
        }
 
        update(min);
    }

    return parent;
}


/// @brief 从dijkstra结果矩阵中提取最短路径
/// @param parent 父节点数组
/// @param start 起点
/// @param end 终点
/// @return 路径
vector<int>
dijkstra_getpath (
    const vector<int>& parent,
    int start,
    int end
) {
    vector<int> path;
    for (int current = end; current != start; current = parent[current]) {
        path.push_back(current);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

void test () {

    auto filename = "./adjacency_matrix.log";
    save_matrix_to_file(randomly_generated_adjacency_matrix(10), filename);    
    auto matrix = load_matrix_from_file(filename);
    std::cout << "matrix:\n"; print_matrix(matrix);

    auto solution1 = floyd_solution(matrix);
    vector<vector<int>> solution2;
    for (int i = 0; i < 10; i++) {
        solution2.push_back(dijkstra_solution(matrix, i));
    }

    for (int start = 0; start < 10; start++)
    for (int end   = 0; end   < 10; end  ++) {
        if (start == end) { continue; }
        auto path1 = floyd_getpath(solution1, start, end);
        auto path2 = dijkstra_getpath(solution2[start], start, end);

        std::cout << "from " << start << " to " << end << ":\n";
        for (auto &i : path1) { std::cout << i << ' '; } std::cout << "\n";
        for (auto &i : path2) { std::cout << i << ' '; } std::cout << "\n";

        if (path1 != path2) {
            // 检查路径权值是否相等
            int weight1 = 0;
            int weight2 = 0;
            for (int i = 0; i < path1.size() - 1; i++) {
                weight1 += matrix[path1[i]][path1[i+1]];
            }
            for (int i = 0; i < path2.size() - 1; i++) {
                weight2 += matrix[path2[i]][path2[i+1]];
            }
            if (weight1 == weight2) {
                std::cout << "The weights of the paths are equal. No error." << std::endl;
            } else {
                std::cout << "[ERROR] The weights of the paths are not equal!!!" << std::endl;
                exit(1);
            }
        }
    }

    std::cout << "[DONE] pass the test!" << std::endl;
}

int main () {
    test();
}
