#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

template<class Rep, class Period = std::ratio<1>>
void wait(std::chrono::duration<Rep, Period> duration) {
    
    std::chrono::time_point<std::chrono::system_clock> _time;
    std::mutex _m;
    std::condition_variable _cv;
    
    _time = std::chrono::system_clock::now();
    _time += duration;

    std::unique_lock<std::mutex> lk(_m);
    _cv.wait_until(lk, _time);
}


/*
    lock_guard<mutex>  强制整个生命周期占有锁
    unique_lock<mutex> 不强制整个生命周期占有锁

    mutex m 互斥量 用来锁住线程
    condition_variable cv 条件变量 用来决定解锁谁
    
    cv.wait()       达成条件
        1參是一个unique<mutex>
        2參是一个lambda -> bool
    cv.wait_for()   达成条件 或达到时间间隔
        1參同上
        2參 std::chrono::duration
        3參=上的2參
    cv.wait_until() 达成条件 或达到某一时刻
        1参3參同上
        2參 到用的时候再说
    
    如果wait时条件就为true 那么不会等待cv.notify_one()而直接跳过阻塞直接执行
    如果wait时条件为false 那么会等待cv.notify_one() 且条件为true时才执行 
    如果不填 或者永远return false 则不用判断条件 notify了就执行
*/

