#include <iostream>
#include <mutex>
#include <omp.h>

#include "random_tools.h"

extern void Random1(const int);
extern void Random2(const int);

std::mutex mutex;

void Random() {
    std::vector<int> res;
    for (unsigned i = 0; i < 10; ++i) {
        res.push_back(lib_tools::Random::RandInt(0, 100));
    }

    std::lock_guard<std::mutex> lock(mutex);
    for (auto itr : res) {
        std::cout << itr << " ";
    }
    std::cout << std::endl;
}

int cnt = 0;

class FooS {
public:
    FooS() : cnt(0) {  }

    static FooS &Instance() {
        static FooS *foosp = nullptr;

        std::lock_guard<std::mutex> lock(mutex);

        if (nullptr == foosp) {
            foosp = new FooS();
        }
        return *foosp;
    }


    void Add() {
        std::lock_guard<std::mutex> lock(mutex);

        for (unsigned i = 0; i < 100; ++i) {
            ++cnt;
        }
        std::lock_guard<std::mutex> zlock(mutex);
        std::cout << "Add end" << std::endl;

    }

    int cnt;
};

void Add() {
    std::lock_guard<std::mutex> lock(mutex);
    for (unsigned i = 0; i < 100; ++i) {
        ++cnt;
    }
    std::cout << "Add end" << std::endl;
}

int main(int argc, char **argv) {
    //Random1(argc);
    //Random2(argc);

    FooS::Instance();

    #pragma omp parallel num_threads(8)
    {
        for (unsigned i = 0; i < 10; ++i)
            FooS::Instance().Add();
    }
    std::cout << FooS::Instance().cnt << std::endl;
    int corenum = omp_get_num_threads();

    std::cout << corenum << std::endl;

    return 0;
}
