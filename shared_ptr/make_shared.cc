#include <memory>
#include <iostream>

using namespace std;

class Foo
{
public:
    Foo() :__i(1) { std::cout << "Constructor Int" << std::endl; };
    ~Foo() { std::cout << "Destructor ~Int" << std::endl; };   
    int data() { return __i; };
    void set_data(int data) { __i = data;};
private:
    int __i;
};

// shared_ptr 作为参数传递给一个函数，引用计数+1
void shared(shared_ptr<Foo> p) 
{
    p->set_data(10);
    cout << "shared data: " << p->data() << endl; // 10
    // shared_ptr 拷贝时，引用计数+1
    shared_ptr<Foo> q(p);
    q->set_data(100);
    cout << "shared data: " << p->data() << endl; // 100
    cout << p.use_count() << endl; // 3
}

int main()
{
    shared_ptr<Foo> p = make_shared<Foo>();
    cout << "shared data: " << p->data() << endl; // 1
    shared(p);
    cout << "shared data: " << p->data() << endl; // 100
    cout << p.use_count() << endl; // 1


    // 两个shared_ptr拷贝的情况
    auto p2 = make_shared<Foo>();
    auto p3(p2);
    auto p4 = make_shared<Foo>();
    
    // 注意：这里p3赋值给了p4
    // 首先看p3, p2 -> p2, 因此p2.use_count = 2, 这里 p4 = p3, 会发生两个事情
    // p4.use_count递减至0, 触发destrocutor
    // p4 -> p2, p2.use_count = 3
    p4 = p3; 
    cout << "p2.use_count(): " << p2.use_count() << endl;    
}