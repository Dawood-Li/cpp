#pragma once

/**
自动持久化
last edited on 20230624
Author: dawood li
E-mail: dawood_li@outlook.com
qq: 1285281563

此类将加载一个文件 将文件的每行作为std::string 用于构造对象并保存至容器中
对象类型由模板参数提供 文件名由构造函数提供

此类是vector的子类 支持vector的一切操作

此类在手动调用save或析构时 将所有元素通过标准输出并保存至原文件

代码仅供参考 仅在一个代码中被使用 目前不具备通用性

请提供宝贵建议
*/

#include <vector>

template<class T>
class File_Loader : public std::vector<T> {

public:

    Data() = default;

    Data(const std::string& filename) {
        load(filename);
    }
    
    ~Data() {
        if (filename.size()) {
            save();
        }
    }

    void load(const std::string& filename) {
        this->filename = filename;
        std::ifstream infile(filename);
        for (std::string line; std::getline(infile, line); this->emplace_back(line));
    }

    void save() {
        std::ofstream outfile(filename);
        for (auto& a : *this) { outfile << a << "\n"; }
    }

private:

    std::string filename;
};
