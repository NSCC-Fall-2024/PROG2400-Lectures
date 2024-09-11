#include <iostream>

int main(int argc, char *argv[]) {
    for (auto i = 1; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    if (argc > 1) {
        std::cout << "You want to edit: " << argv[1] << std::endl;
    } else {
        std::cout << "Format: command_line <filename>" << std::endl;
    }

    return 0;
}
