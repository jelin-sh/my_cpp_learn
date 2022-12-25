# My C++ Learn

This repository is my learn of the c plus plus and test project

## 1. build

```bash
git clone https://gitee.com/skjsnb/my-cpp-learn.git
cd my-cpp-learn/stl_thread
mkdir -p build/debug
cmake . -B build/debug
cd build/debug/
make -j
```

## 2. Record

1. std::move 可以将左值转换为右值
2. std::forward 需配合模板引用折叠使用，实现完美转发
3. std::thread 创建后立即执行，但是如果父线程结束则创建的线程立即结束，所以父线程创建线程结束后，需要考虑是否将创建的线程脱离（detach）或者阻塞运行等待线程结束（join）
4. STL并不支持thread group, 但可以用``` std::vector<std::thread>``` 实现，其中增加线程成员使用 ```emplace_back```方法，全部阻塞（join）或者脱离（detach）需遍历实现

```c++
TEST(Test_Thread, ThreadGroup) {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(
            [](int arg) {
                std::cout << "lambda: " << arg << std::endl;
            },
            i
        );
    }
    for (auto& t : threads) {
        t.join();
    }
}
```

5. std::thread 支持lambda匿名函数
6. 当静态成员变量为常量时，可以直接初始化，也可以在类外部初始化







