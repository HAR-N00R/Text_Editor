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


    //Search fucntion
    bool search(std::string& text) const;
    void replaceText(const std::string& text, const std::string& replaceWith, std::size_t line);
    void replaceAllText(const std::string& text, const std::string& replaceWith);

    //Statistics
    void displayStatistics() const;

    //Helper Functions Below
    bool documentValidity() const;
    bool documentValidity(std::size_t index) const;
    std::size_t wordCounter() const;
};

#endif
