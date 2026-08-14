#ifndef TEXT_EDITOR_TEXTEDITOR_H
#define TEXT_EDITOR_TEXTEDITOR_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class TextEditor {
    private:
    std::vector <std::string> document;

    public:
    void displayDocument() const;
    void addLine(const std::string& text);
    void editLine(const std::string& text, std::size_t index);
    void deleteLine(std::size_t index);
    void clearDocument();


    //File I/O
    void saveDocument();
    void loadDocument();


    //Helper Functions Below
    bool documentValidity(std::size_t index) const;
};

#endif