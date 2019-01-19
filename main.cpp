#include <iostream>
#include "function.h"
using std::cout;
using std::endl;
using my::function;

void q() {
    cout << 2 << endl;
}

int some(int a) {
    return a * 2;
}

struct functor {
    int operator()() {
        return 1;
    }
};

int main()
{
    /*
    cout << "Hello World!" << endl;
    function<void()> f = []() { cout << 1 << endl; };
    f();
    f = g;
    f();
    function<int(int)> some2 = some;
    cout << some2(5) << endl;
    function<int()> k = functor();
    cout << k() << endl;
    */
    /*
    function<void()> f(nullptr);
    if (f) { f(); };
    */
    function<void()> f = []() { cout << 1 << endl; };
    function<void()> g(f);
    cout << "In g(): " << endl;
    g();
    cout << "In f(): " << endl;
    f();
    cout << endl;
    function<void()> k(std::move(f));
    cout << "In g(): " << endl;
    g();
    cout << "In k(): " << endl;
    k();
    cout << "In f(): " << endl;
    if (f) { f(); };
    return 0;
}
