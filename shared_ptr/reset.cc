#include <memory>
#include <iostream>

using namespace std;

class Foo
{
public:
    Foo() :__i(1) { std::cout << "Constructor Foo()" << std::endl; };
    explicit Foo(int i) :__i(i) { std::cout << "Constructor explicit Foo(int i)" << std::endl; };
    ~Foo() { std::cout << "Destructor ~Foo" << std::endl; };   
    int data() { return __i; };
    void set_data(int data) { __i = data;};
private:
    int __i;
};


int main()
{
    shared_ptr<Foo> p = make_shared<Foo>(10);
    p.reset(new Foo(20)); // 此时计数器值为1, 因此原有的Foo=10会被释放
    cout << p->data()  << endl;

    auto cp(p);
    // 此时计数器值为2, 因此原有的Foo=20不会被释放（cp进行了拷贝，计数值递增了），当前的p指向Foo=30
    p.reset(new Foo(30)); 
    cout << p->data() << ", " << cp->data() << endl;
}