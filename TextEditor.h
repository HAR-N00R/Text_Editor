#ifndef TEXT_EDITOR_TEXTEDITOR_H
#define TEXT_EDITOR_TEXTEDITOR_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

class TextEditor {
    private:
    std::vector <std::string> document;
    std::string currentFile;
    bool modified = false;
    std::stack<std::vector<std::string>> undoStack;
    std::stack<std::vector<std::string>> redoStack;

    std::string getCurrentFile() const;
    void setCurrentFile(const std::string& file);
    bool getModified() const;
    void setModified(bool modified);

    //Helper Functions Below
    std::size_t wordCounter() const;
    void save(const std::string& path);
    void emptyRedoStack();
    void saveState();
    void saveState(const std::vector<std::string>& originalDocument);


    public:
    void displayDocument() const;
    void addLine(const std::string& text);
    void editLine(const std::string& text, std::size_t index);
    void deleteLine(std::size_t index);
    void clearDocument();


    //File I/O
    void saveDocument();
    void saveAsDocument();
    void loadDocument();


    //Search fucntion
    bool search(const std::string& text) const;
    void replaceText(const std::string& text, const std::string& replaceWith, std::size_t line);
    void replaceAllText(const std::string& text, const std::string& replaceWith);

    //Statistics
    void displayStatistics() const;

    //Helper Functions Below
    bool documentValidity() const;
    bool documentValidity(std::size_t index) const;
    bool isModified() const;
    void clearPath();

    //Undo/Redo
    void undo();
    void redo();

};

#endif
