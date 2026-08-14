#include <iostream>
#include "TextEditor.h"

template <typename datatype>
void inputValidator(datatype& input)
{
    std::cout << "Input : ";
    std::cin >> input;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "invalid input, Please reenter" << std::endl << "Input: ";;
        std::cin >> input;
    }
    std::cin.ignore(1000, '\n');
    std::cout << std::string(60,'=') << std::endl;
}

int menu() {

    std::cout << "Please select one of the following operations:" << std::endl;
    std::cout << " 1. Add Line to Document" << std::endl;
    std::cout << " 2. Display Document" << std::endl;
    std::cout << " 3. Edit Line" << std::endl;
    std::cout << " 4. Delete Line" << std::endl;
    std::cout << " 5. Clear Document" << std::endl;
    std::cout << " 6. Save Document" << std::endl;
    std::cout << " 7. Load File" << std::endl;
    std::cout << " 8. Quit" << std::endl;

    int input;
    inputValidator(input);

    while (true) {
        if (input == 1 || input == 2 || input == 3 || input == 4 || input == 5 || input == 6 || input == 7 || input == 8) {
            return input;
        }
        else {
            std::cout << "Invalid input" << std::endl;
            std::cout << std::string(60,'=') << std::endl;
            std::cout << "Please select one of the following operations:" << std::endl;
            std::cout << " 1. Add Line to Document" << std::endl;
            std::cout << " 2. Display Document" << std::endl;
            std::cout << " 3. Edit Line" << std::endl;
            std::cout << " 4. Delete Line" << std::endl;
            std::cout << " 5. Clear Document" << std::endl;
            std::cout << " 6. Save Document" << std::endl;
            std::cout << " 7. Load File" << std::endl;
            std::cout << " 8. Quit" << std::endl;
            inputValidator(input);
        }
    }
}

int main()
{
    std::cout << std::string(60,'=') << std::endl;
    std::cout << "Welcome to Terminal text Editor" << std::endl;
    std::cout << std::string(60,'=') << std::endl;
    TextEditor textEditor;
    std::string line;

    int input = menu();

    while (true) {
        if (input == 1) {
            std::cout << "Please enter text: ";
            std::getline(std::cin, line);
            std::cout << std::string(60,'=') << std::endl;
            textEditor.addLine(line);
            input = menu();
        }
        else if (input == 2) {
            std::cout << "Displaying stored text below:" << std::endl;
            textEditor.displayDocument();
            input = menu();
        }
        else if (input == 3) {
            std::size_t index;
            std::cout << "Enter line to edit: ";
            inputValidator(index);
            while (index == 0) {
                std::cout << "invalid Line Number" << std::endl;
                std::cout << "Enter line to delete: ";
                inputValidator(index);
            }
            index--;
            std::cout << "Enter replacement: ";
            std::getline(std::cin, line);
            std::cout << std::string(60,'=') << std::endl;
            textEditor.editLine(line,index);
            input = menu();
        }
        else if (input == 4) {
            std::size_t index;
            std::cout << "Enter line to delete: ";
            inputValidator(index);
            while (index == 0) {
                std::cout << "invalid Line Number" << std::endl;
                std::cout << "Enter line to delete: ";
                inputValidator(index);
            }
            index--;
            textEditor.deleteLine(index);
            input = menu();

        }
        else if (input == 5) {
            textEditor.clearDocument();
            input = menu();
        }
        else if (input == 6) {
            textEditor.saveDocument();
            input = menu();
        }
        else if (input == 7) {
            textEditor.loadDocument();
            input = menu();
        }
        else if (input == 8) {
            return 0;
        }
    }
}
