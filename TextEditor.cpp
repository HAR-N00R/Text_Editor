#include "TextEditor.h"


void TextEditor::displayDocument() const {
    if (document.empty()) {
        std::cout << "Document is Empty" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
    }
    else {
        for (std::size_t i = 0; i < document.size(); i++) {
            std::cout << (i + 1) << ": " << document[i] << std::endl;
        }
            std::cout << std::string(60,'=') << std::endl;
    }
}

void TextEditor::addLine(const std::string& text) {
    document.push_back(text);
}

void TextEditor::editLine(const std::string& text, std::size_t index) {
    if (!documentValidity(index)) {
        return;
    }
    document[index] = text;

}

void TextEditor::deleteLine(std::size_t index) {
    if (!documentValidity(index)) {
        return;
    }
    document.erase(document.begin() + index);
}

void TextEditor::clearDocument() {
    if (document.empty()) {
        std::cout << "Document is already Empty" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
    }
    else {
        std::cout << "Clearing document" << std::endl;
        document.clear();
        std::cout << std::string(60,'=') << std::endl;
    }
}

//File I/O

void TextEditor::saveDocument() {
    std::string path;
    std::cout << "Enter the file path where to save the document: ";
    std::getline(std::cin, path);

    std::ofstream file(path);
    if (!file) {
        std::cout << "Failed to open file." << std::endl;
    }
    else {
        for (std::size_t i = 0; i < document.size(); i++) {
            file << document[i] << std::endl;
        }
        std::cout << "Save Successful" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
    }
}

void TextEditor::loadDocument() {
    if (!document.empty()) {
        std::cout << "Document is not Empty" << std::endl;
        std::cout << "Please save or clear document" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
        return;
    }

    std::string path;
    std::cout << "Enter the file path where to load the document: ";
    std::getline(std::cin, path);

    std::ifstream file(path);
    if (!file) {
        std::cout << "Failed to open file." << std::endl;
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            document.push_back(line);
        }
        std::cout << "Load Successful" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
    }
}


//helper function
bool TextEditor::documentValidity(std::size_t index) const {
    if (document.empty()) {
        std::cout << "Document is Empty" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
        return false;
    }
    if (index >= document.size()) {
        std::cout << "Invalid index" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
        return false;
    }
    return true;
}
