#include <iostream>

extern "C" void hello_rust();

int main() {
    std::cout << "Hello from C++!" << std::endl;
    hello_rust();
    return 0;
}

