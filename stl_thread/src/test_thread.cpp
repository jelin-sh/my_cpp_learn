//
// Created by Jelin on 2022/12/25.
//

#include "gtest/gtest.h"
#include <thread>
#include <utility>

void foo(int arg) {
    std::cout << "foo: " << arg << std::endl;
}

TEST(Test_Thread, Static_Func) {
    std::thread t1(foo, 1);
    std::thread t2(foo, 2);
    std::thread t3(foo, 3);
    t1.join();
    t2.join();
    t3.join();
}

TEST(Test_Thread, Lambda) {
    std::thread t1(
        [](int arg) {
            std::cout << "lambda: " << arg << std::endl;
        },
        1
    );
    std::thread t2(
        [](int arg) {
            std::cout << "lambda: " << arg << std::endl;
        },
        2
    );
    std::thread t3(
        [](int arg) {
            std::cout << "lambda: " << arg << std::endl;
        },
        3
    );
    t1.join();
    t2.join();
    t3.join();
}

class my_string {
    friend std::ostream& operator<<(std::ostream&, const my_string&);

public:
    explicit my_string(const std::string& str) {
        m_str = str;
        std::cout << "my_string: " << m_str << std::endl;
    }

    /* 拷贝构造 */
    my_string(const my_string& other) noexcept {
        std::cout << "copy constructor" << std::endl;
        m_str = other.m_str;
    }

    /* 移动构造 */
    my_string(my_string&& other) noexcept: m_str(std::move(other.m_str)) {
        std::cout << "move constructor" << std::endl;
    }

public:
    const std::string& get_str() const {
        return m_str;
    }

    void set_str(const std::string& str) {
        m_str = str;
    }

private:
    std::string m_str;
};

std::ostream& operator<<(std::ostream& out, const my_string& string) {
    out << string.m_str;
    return out;
}

template<class T>
class Foo {
public:
    explicit Foo(T&& prefix): m_prefix(std::forward<T>(prefix)) { }

    void func(int arg) const {
        std::cout << m_prefix << ": " << arg << std::endl;
    }

    T m_prefix;
};

TEST(Test_Thread, Member_Func) {

    my_string s1("This is s1");  //normal
    my_string s2 = s1;           // 拷贝赋值
    s2.set_str("This is s2");
    my_string s3 = static_cast<my_string&&>(s1);  // 移动赋值, 移动之后s1的字符串为空

    typedef Foo<my_string> l_foo_t;
    typedef Foo<my_string&> r_foo_t;
    std::cout << "----" << std::endl;
    r_foo_t l_foo(s2);
    std::cout << "----" << std::endl;
    l_foo_t l_foo1(my_string("Hello"));
    std::cout << "----" << std::endl;

    std::thread t1(&r_foo_t::func, &l_foo, 1);
    std::thread t2(&r_foo_t::func, &l_foo, 2);
    std::thread t3(&r_foo_t::func, &l_foo, 3);
    t1.join();
    t2.join();
    t3.join();

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
}

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

TEST(Test_Thread, ThreadDetach) {
    using namespace std::chrono_literals;
    std::function<void()> func = []() {
        std::thread t(foo, 1);
        t.detach();
    };
    func();
    std::this_thread::sleep_for(3s);
}

class class_demo {
public:
    static void print() {
        std::cout << "class_demo:: " << m_i << std::endl;
    }

private:
    const static int m_i = 100;
};

TEST(Test_Thread, Static_Member) {
    std::thread t(&class_demo::print);
    t.join();
}