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
#include <fstream>
#include <iostream>

template<class T>
class File_Loader : public std::vector<T> {

private:

    std::string filename;

public:

    File_Loader () = default;

    File_Loader (
        const std::string& filename
    ) {
        load(filename);
    }
    
    ~File_Loader () {
        if (filename.size()) {
            save();
        }
    }

    void
    load (
        const std::string& filename
    ) {
        this->filename = filename;
        std::ifstream infile(filename);
        for (std::string line; std::getline(infile, line); this->emplace_back(line));
    }

    void
    save() {
        std::ofstream outfile(filename);
        for (auto& a : *this) {
            std::cout << a << std::endl;
            outfile << a << "\n";
        }
    }
};


#include <string>
#include <sstream>

inline
std::string
load_binary (
    const std::string& filename
) {
    auto ifs = std::ifstream(filename);
    return std::string(
        std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>()
    );
}

inline
void
write_binary (
    const std::string& filename,
    const std::string& filedata
) {
    std::ofstream(filename, std::ios::binary).write(filedata.c_str(), filedata.size());
}

inline
std::vector<std::string>
load_text (
    const std::string& filename
) {
    std::vector<std::string> lines;
    auto ifs = std::ifstream(filename);
    for (std::string line; std::getline(ifs, line); lines.push_back(std::move(line)));
    return lines;
}

void
write_text (
    const std::string& filename,
    const std::vector<std::string>& lines
) {
    auto log = std::ofstream(filename);
    for (auto& line : lines) {
        log << line << "\n";
    }
}
