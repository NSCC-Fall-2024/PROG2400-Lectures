#include <iostream>

int main() {

    int num = 0x1234;

    auto ptr = (char *)&num;

    std::cout << std::hex << "num = " << num << std::endl;
    std::cout << std::hex << "ptr = " << ptr << std::endl;
    std::cout << "*ptr = " << *ptr << std::endl;

    return 0;
}
