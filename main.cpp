//#include "interpreter.h"
#include <vector>
#include <iostream>
#include <fstream>


class Apple{
public:
    int a;
    explicit Apple(int _a): a(_a){
        std::cout << "Created " << _a << std::endl;
    }
    bool operator==(const Apple& other){
        std::cout << "==" << std::endl;
        return a == other.a;
    }
};
int main() {
//    TestBase a;
//    Interpreter console(a);
//    console.run();
    for(auto a = Apple(0); !(a == Apple(5));++a.a){
        std::cout << "Lets go" << std::endl;
    }
}







