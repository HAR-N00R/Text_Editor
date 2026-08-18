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
    std::cout << " 3. Search Line" << std::endl;
    std::cout << " 4. Replace text" << std::endl;
    std::cout << " 5. Edit Line" << std::endl;
    std::cout << " 6. Delete Line" << std::endl;
    std::cout << " 7. Clear Document" << std::endl;
    std::cout << " 8. Display Statistics" << std::endl;
    std::cout << " 9. Save Document" << std::endl;
    std::cout << " 10. Save As " << std::endl;
    std::cout << " 11. Load File" << std::endl;
    std::cout << " 12. Undo" << std::endl;
    std::cout << " 13. Redo" << std::endl;
    std::cout << " 14. Quit" << std::endl;

    int input;
    inputValidator(input);

    while (true) {
        if (input == 1 || input == 2 || input == 3 || input == 4 || input == 5 || input == 6 || input == 7 || input == 8
            || input == 9 || input == 10 || input == 11 || input == 12 || input == 13 || input == 14) {
            return input;
        }
        else {
            std::cout << "Invalid input" << std::endl;
            std::cout << std::string(60,'=') << std::endl;
            std::cout << "Please select one of the following operations:" << std::endl;
            std::cout << " 1. Add Line to Document" << std::endl;
            std::cout << " 2. Display Document" << std::endl;
            std::cout << " 3. Search text" << std::endl;
            std::cout << " 4. Replace text" << std::endl;
            std::cout << " 5. Edit Line" << std::endl;
            std::cout << " 6. Delete Line" << std::endl;
            std::cout << " 7. Clear Document" << std::endl;
            std::cout << " 8. Display Statistics" << std::endl;
            std::cout << " 9. Save Document" << std::endl;
            std::cout << " 10. Save As " << std::endl;
            std::cout << " 11. Load File" << std::endl;
            std::cout << " 12. Undo" << std::endl;
            std::cout << " 13. Redo" << std::endl;
            std::cout << " 14. Quit" << std::endl;
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
            if (!textEditor.documentValidity()) {
                input = menu();
            }
            else {
                std::cout << "Search: ";
                std::string text;
                std::getline(std::cin, text);
                textEditor.search(text);
                input = menu();
            }
        }
        else if (input == 4) {
            if (!textEditor.documentValidity()) {
                input = menu();
            }
            else {
                std::cout << "Replace text: ";
                std::string text;
                std::getline(std::cin, text);
                if (textEditor.search(text)) {
                    std::cout << "1. Replace All" << std::endl << "2. Replace in Specific Line" << std::endl;
                    int option;
                    inputValidator(option);
                    std::string replaceWith;
                    std::cout << "Replace with: ";
                    std::getline(std::cin, replaceWith);
                    if (option == 1) {
                        textEditor.replaceAllText(text,replaceWith);
                    }
                    else if (option == 2) {
                        std::cout << "Enter Line where to replace text" << std::endl;
                        int lineNumber;
                        inputValidator(lineNumber);
                        while (lineNumber <= 0) {
                            std::cout << "invalid Line Number" << std::endl;
                            std::cout << "Enter line to edit: ";
                            inputValidator(lineNumber);
                        }
                        lineNumber--;
                        textEditor.replaceText(text,replaceWith,lineNumber);
                    }
                }
                input = menu();
            }
        }
        else if (input == 5) {
            std::size_t index;
            std::cout << "Enter line to edit: ";
            inputValidator(index);
            while (index == 0) {
                std::cout << "invalid Line Number" << std::endl;
                std::cout << "Enter line to edit: ";
                inputValidator(index);
            }
            index--;
            std::cout << "Enter replacement: ";
            std::getline(std::cin, line);
            std::cout << std::string(60,'=') << std::endl;
            textEditor.editLine(line,index);
            input = menu();
        }
        else if (input == 6) {
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
        else if (input == 7) {
            textEditor.clearDocument();
            input = menu();
        }
        else if (input == 8) {
            textEditor.displayStatistics();
            input = menu();
        }
        else if (input == 9) {
            textEditor.saveDocument();
            input = menu();
        }
        else if (input == 10) {
            textEditor.saveAsDocument();
            input = menu();
        }
        else if (input == 11) {
            if (textEditor.isModified()) {
                std::cout << "Document contains unsaved modifications" << std::endl;
                std::cout << std::string(60,'=') << std::endl;
                std::cout << "Please select one of the operations:" << std::endl;
                std::cout << "1. Save" << std::endl << "2. Override Load" << std::endl << "3. Exit to Main Menu" <<
                    std::endl;
                int option;
                inputValidator(option);
                while (option != 1 && option != 2 && option != 3) {
                    std::cout << "Invalid selection" << std::endl;
                    std::cout << "Please select one of the operations:" << std::endl;
                    std::cout << "1. Save" << std::endl << "2. Override Load" << std::endl << "3. Exit to Main Menu" <<
                        std::endl;
                    inputValidator(option);
                }
                if (option == 1) {
                    textEditor.saveDocument();
                    textEditor.clearPath();
                    textEditor.loadDocument();
                    input = menu();
                }
                else if (option == 2) {
                    textEditor.clearPath();
                    textEditor.loadDocument();
                    input = menu();
                }
                else if (option == 3) {
                    input = menu();
                }
            }
            else {
                textEditor.loadDocument();
                input = menu();
            }
        }
        else if (input == 12) {
            textEditor.undo();
            input = menu();
        }
        else if (input == 13) {
            textEditor.redo();
            input = menu();
        }
        else if (input == 14) {
            return 0;
        }
    }
}