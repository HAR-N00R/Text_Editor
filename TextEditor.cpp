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
    saveState();
    document.push_back(text);
    setModified(true);
}

void TextEditor::editLine(const std::string& text, std::size_t index) {
    if (!documentValidity(index)) {
        return;
    }
    
    saveState();
    document[index] = text;
    setModified(true);

}

void TextEditor::deleteLine(std::size_t index) {
    if (!documentValidity(index)) {
        return;
    }
    
    saveState();
    document.erase(document.begin() + index);
    setModified(true);
}

void TextEditor::clearDocument() {
    if (document.empty()) {
        std::cout << "Document is already Empty" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
    }
    else {
        saveState();
        std::cout << "Clearing document" << std::endl;
        document.clear();
        setModified(true);
        std::cout << std::string(60,'=') << std::endl;
    }
}

//File I/O

std::string TextEditor::getCurrentFile() const {
    return currentFile;
}

void TextEditor::setCurrentFile(const std::string& file) {
    currentFile = file;
}

bool TextEditor::getModified() const {
    return modified;
}

void TextEditor::setModified(bool modified) {
    this->modified = modified;
}

void TextEditor::saveDocument() {
    std::string path = getCurrentFile();
    if (path.empty()) {
        std::cout << "Enter the file path where to save the document: ";
        std::getline(std::cin, path);
    }
    save(path);
}

void TextEditor::saveAsDocument() {
    std::string path;
    std::cout << "Enter the file path where to save the document: ";
    std::getline(std::cin, path);
    save(path);
}

void TextEditor::save(const std::string& path) {
    std::ofstream file(path);
    if (!file) {
        std::cout << "Failed to open file." << std::endl;
    }
    else {
        setCurrentFile(path);
        for (std::size_t i = 0; i < document.size(); i++) {
            file << document[i] << std::endl;
        }
        std::cout << "Save Successful" << std::endl;
        setModified(false);
        std::cout << std::string(60,'=') << std::endl;
    }
}

void TextEditor::loadDocument() {
    std::string path = getCurrentFile();
    if (path.empty()) {
        std::cout << "Enter the file path where to load the document: ";
        std::getline(std::cin, path);
    }

    std::ifstream file(path);
    if (!file) {
        std::cout << "Failed to open file." << std::endl;
    }
    else {
        document.clear();
        setCurrentFile(path);
        std::string line;
        while (std::getline(file, line)) {
            document.push_back(line);
        }
        std::cout << "Load Successful" << std::endl;
        setModified(false);
        std::cout << std::string(60,'=') << std::endl;
    }
}


bool TextEditor::search(const std::string& text) const {
    if (!documentValidity()) {
        std::cout << "Document is Empty" << std::endl;
        return false;
    }
    int found = 0;
    for (std::size_t i = 0; i < document.size(); i++) {
        if (document[i].find(text) != std::string::npos) {
            found++;
            if (found == 1) {
                std::cout << "Text found on the following lines:" << std::endl;
            }
            std::cout << (i + 1) << ": " << document[i] << std::endl;
        }
    }
    if (found == 0) {
        std::cout << "Not found" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
        return false;
    }
    std::cout << std::string(60,'=') << std::endl;
    std::cout << "Found " << found << " lines containing text" << std::endl;
    std::cout << std::string(60,'=') << std::endl;
    return true;
}


void TextEditor::replaceText(const std::string& text, const std::string& replaceWith, std::size_t line) {
    if (!documentValidity() || text.empty()) {
        return;
    }
    if (line >= document.size()) {
        std::cout << "Invalid line number" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
        return;
    }
    if (document[line].find(text) != std::string::npos) {

        saveState();
        std::cout << "Text replaced" << std::endl;
        setModified(true);
        document[line].replace(document[line].find(text),text.length(),replaceWith);
        std::cout << std::string(60,'=') << std::endl;
    }
    else {
        std::cout << "Nothing to Replace" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
    }
}



void TextEditor::replaceAllText(const std::string& text, const std::string& replaceWith) {
    if (!documentValidity() || text.empty()) {
        return;
    }
    int replaced = 0;
    int occurrences = 0;
    std::vector<std::string> backup = document;
    for (std::size_t i = 0; i < document.size(); i++) {
        bool textFound = false;
        std::size_t pos = 0;
        while ((pos = document[i].find(text,pos)) != std::string::npos) {
            occurrences++;
            document[i].replace(pos,text.length(),replaceWith);
            textFound = true;
            pos += replaceWith.length();
        }
            if (textFound) {
                replaced++;
            }
    }
    std::cout << std::string(60,'=') << std::endl;
    if (replaced > 0) {
        setModified(true);
        saveState(backup);
        std::cout << "Replaced " << occurrences << " occurrences on " << replaced << " lines containing text" << std::endl;
    }
    if (replaced == 0) {
        std::cout << "Nothing to Replace" << std::endl;
    }
    std::cout << std::string(60,'=') << std::endl;
}


void TextEditor::displayStatistics() const {
    if (!documentValidity()) {
        return;
    }
    std::size_t characters = 0;
    for (std::size_t i = 0; i < document.size(); i++) {
        characters += document[i].length();
    }
    std::cout << "Characters: " << characters << std::endl;
    std::cout << "Words: " << wordCounter() << std::endl;
    std::cout << "Lines: " << document.size() << std::endl;
    std::cout << std::string(60,'=') << std::endl;
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

bool TextEditor::documentValidity() const {
    if (document.empty()) {
        std::cout << "Document is Empty" << std::endl;
        std::cout << std::string(60,'=') << std::endl;
        return false;
    }
    return true;
}

std::size_t TextEditor::wordCounter() const {
    std::size_t words = 0;

    for (std::size_t i = 0; i < document.size(); i++) {
        const std::string& line = document[i];
        bool word = false;
        for (char x: line) {
            if (!std::isspace(x)) {
                word = true;
            }
            else if (word) {
                words++;
                word = false;
            }
        }
        if (word) {
            words++;
        }
    }
    return words;
}

bool TextEditor::isModified() const {
    return getModified();
}

void TextEditor::clearPath() {
    setCurrentFile("");
}

// Undo/Redo
void TextEditor::undo() {
    if (undoStack.empty()) {
        std::cout << "Undo unavailble" << std::endl;
        return;
    }
    redoStack.push(document);
    document = undoStack.top();
    undoStack.pop();
    modified = true;
}

void TextEditor::redo() {
    if (redoStack.empty()) {
        std::cout << "Redo unavailble" << std::endl;
        return;
    }
    undoStack.push(document);
    document = redoStack.top();
    redoStack.pop();
    modified = true;
}

void TextEditor::emptyRedoStack() {
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void TextEditor::saveState() {
    undoStack.push(document);
    emptyRedoStack();
}

void TextEditor::saveState(const std::vector<std::string>& originalDocument) {
    undoStack.push(originalDocument);
    emptyRedoStack();
}
