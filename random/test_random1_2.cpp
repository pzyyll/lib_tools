#include <iostream>

extern void Random1(const int);
extern void Random2(const int);

int main(int argc, char **argv) {
    Random1(argc);
    Random2(argc);

    return 0;
}
