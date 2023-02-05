#include <iostream>
#include <set>


void print_set(std::set<int>& buffer){
    for (auto& item:buffer) {
        std::cout << item << " ";
    }
    std::cout << "\r\n";
}

void foo1(){
    std::set<int> buf;
    buf.insert(10);
    buf.insert(5);
    buf.insert(10);
    print_set(buf);
}

void traversal_set(std::set<int>& buffer){
    // 方式1：使用基于范围的for循环
    for (auto& item:buffer) {
        std::cout << item << " ";
    }
    std::cout << "\r\n";
    // 方式2：使用迭代器
    auto it = buffer.begin();
    while (it != buffer.end()){
        std::cout << *it << " ";
        it++;
    }
    std::cout << "\r\n";
}

void foo2(){
    std::set<int> buf;
    buf.insert(10);
    buf.insert(5);
    buf.insert(10);
    traversal_set(buf);
}

void foo3(){
    auto cmp = [](int a,int b){return a > b;};
    std::set<int, decltype(cmp)> buf(cmp);
    buf.insert(10);
    buf.insert(5);
    buf.insert(10);

    for (auto& item:buf) {
        std::cout << item << " ";
    }
    std::cout << "\r\n";
}

void foo4(){
    std::set<int> buf;
    buf.insert(10);
    buf.insert(5);
    buf.insert(8);
    buf.erase(5);
    print_set(buf);
}

int main() {
    foo4();
    return 0;
}
