#include <iostream>
#include <sstream>

int main() {

    std::string user_input;
    char command;
    auto start = -1;
    auto end = -1;

    std::cout << "Enter a command: ";
    std::getline(std::cin, user_input);

    std::stringstream ss(user_input);
    ss >> command;

    std::cout << "Command: " << command << std::endl;

    ss >> start;
    if (!ss.fail()) {
        std::cout << "Start: " << start << std::endl;

        ss >> end;
        if (!ss.fail()) {
            std::cout << "End: " << end << std::endl;
        } else {
            if (end == -1) {
                std::cout << "Short Command." << std::endl;
            } else {
                std::cout << "Text: " << user_input << std::endl;
            }
        }
    } else {
        std::cout << "Text: " << user_input << std::endl;
    }

    return 0;
}