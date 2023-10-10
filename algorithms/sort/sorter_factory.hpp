#pragma once
#include "./std_sorter.hpp"
#include "./bubble_sorter.hpp"
#include "./selection_sorter.hpp"
#include "./insertion_sorter.hpp"
#include "./quick_sorter.hpp"
#include "./quick_non_recursive_sorter.hpp"
#include <string>
#include <memory>

template <class T>
class Sorter_Factory {
public:
    static std::shared_ptr<Sorter_Base<T>> create(const std::string& type) {
        if(type == "Std") { 
            return std::make_shared<Std_Sorter<T>>();
        } else if (type == "Bubble") {
            return std::make_shared<Bubble_Sorter<T>>();
        } else if(type == "Selection") { 
            return std::make_shared<Selection_Sorter<T>>();
        } else if(type == "Insertion") { 
            return std::make_shared<Insertion_Sorter<T>>();
        } else if(type == "Quic") { 
            return std::make_shared<Quick_Sorter<T>>();
        } else if(type == "Quic_Non_Recursive") { 
            return std::make_shared<Quick_Non_Recursive_Sorter<T>>();
        } else {
            return nullptr;
        }
    }
};
