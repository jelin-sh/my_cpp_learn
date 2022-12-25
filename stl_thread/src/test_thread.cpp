//
// Created by Jelin on 2022/12/25.
//

#include "gtest/gtest.h"
#include <thread>

void foo(int arg) {
    std::cout << "foo: " << arg << std::endl;
}

TEST(Test_Thread, Static_Func){
    std::thread t1(foo, 1);
    std::thread t2(foo, 2);
    std::thread t3(foo, 3);
    t1.join();
    t2.join();
    t3.join();
}

TEST(Test_Thread, Lambda){
    std::thread t1([](int arg){
        std::cout << "lambda: " << arg << std::endl;
    }, 1);
    std::thread t2([](int arg){
        std::cout << "lambda: " << arg << std::endl;
    }, 2);
    std::thread t3([](int arg){
        std::cout << "lambda: " << arg << std::endl;
    }, 3);
    t1.join();
    t2.join();
    t3.join();
}

