#ifndef TEXT_EDITOR_TEXTEDITOR_H
#define TEXT_EDITOR_TEXTEDITOR_H
#include <string>
#include <vector>
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
    bool save(const std::string& path);
    void emptyUndoStack();
    void emptyRedoStack();
    void saveState();
    void saveState(const std::vector<std::string>& originalDocument);


    public:
    void displayDocument() const;
    void addLine(const std::string& text);
    void editLine(const std::string& text, std::size_t index);
    void deleteLine(std::size_t index);
    void clearDocument();
    bool hasCurrentFile() const;


    //File I/O
    bool saveDocument();
    bool saveAsDocument(const std::string& path);
    bool loadDocument(const std::string& path);


    //Search fucntion
    bool search(const std::string& text) const;
    bool replaceText(const std::string& text, const std::string& replaceWith, std::size_t line);
    bool replaceAllText(const std::string& text, const std::string& replaceWith);

    //Statistics
    void displayStatistics() const;

    //Helper Functions Below
    void isDocumentEmpty() const;
    void isIndexValid(std::size_t index) const;
    bool isModified() const;

    //Undo/Redo
    void undo();
    void redo();

};

#endif
