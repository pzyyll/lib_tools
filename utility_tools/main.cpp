#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <array>
#include <functional>

#include "utility_tools.h"

using namespace std;
using namespace lib_tools;

class Foo {
public:
    Foo(int &mem_refv) : mem_ref(mem_refv) { }

    int &mem_ref;
};

template <typename T, typename ...Args>
T *Create(Args&& ...args) {
    T *new_point = new T(std::forward<Args>(args)...);
    return new_point;
};

int main(int argc, char **argv) {

    int z = 10;

    Foo fooz(z);

    cout << (void *)(&z) << endl;
    cout << (void *)(&fooz.mem_ref) << endl;

    cout << "non correct.---" << endl;
    Foo *foozp = Create<Foo>(z);
    cout << (void *)(&foozp->mem_ref) << endl;
    cout << foozp->mem_ref << endl;
    cout << "non correct.---" << endl;


    cout << "correct1.---" << endl;
    Foo *foozpc = Create<Foo>(std::ref(z));
    cout << (void *)(&foozpc->mem_ref) << endl;
    cout << foozpc->mem_ref << endl;
    cout << "correct1.---" << endl;

    cout << "end" << endl;
    return 0;
}
