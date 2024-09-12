#include <iostream>
#include <span>
#include <vector>

void print_array(auto array) {
    for (auto i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {

    int c_array[] = {1, 2, 3, 4, 5};

    print_array(std::span{c_array, sizeof(c_array) / sizeof(c_array[0])});

    std::vector<int> v;
    for (auto i = 0; i < 5; i++) {
        v.push_back(i + 1);
    }
    print_array(v);

    v.push_back(6);

    print_array(v);

    return 0;
}
