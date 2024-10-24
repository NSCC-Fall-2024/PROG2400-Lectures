#include <iostream>
#include <cstring>

bool is_palindrome(const char *input, size_t len) {
    for (auto i = 0; i < len / 2; ++i) {
        if (input[i] != input[len - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {

    const int BUFFER_SIZE = 80;
    char buffer[BUFFER_SIZE];

    std::cout << "Enter a word: ";
    std::cin.getline(buffer, BUFFER_SIZE);

    if (is_palindrome(buffer, strnlen(buffer, BUFFER_SIZE))) {
        std::cout << buffer << " IS a palindrome." << std::endl;
    } else {
        std::cout << buffer << " IS NOT a palindrome." << std::endl;
    }

    return 0;
}