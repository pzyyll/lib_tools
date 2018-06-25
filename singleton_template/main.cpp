#include <iostream>

#include "singleton.h"

using namespace std;
using namespace lib_tools;

class MainSys {
public:
    MainSys() : a_(12) {
        cout << "Construct " << a_ << endl;
    }

    ~MainSys() {
        cout << "De construct." << endl;
    }

    int a_;
};

typedef singleton<MainSys> MainSysS;

int main() {
    cout << "endl" << endl;
    return 0;
}
