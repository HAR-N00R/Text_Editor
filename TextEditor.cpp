#include "TextEditor.h"
#include <fstream>
#include <stdexcept>

std::size_t TextEditor::getLineCount() const {
    return document.size();
}

const std::string& TextEditor::getCurrentLine(std::size_t index) const {
    isDocumentEmpty();
    isIndexValid(index);
    return document[index];
}

void TextEditor::searchResults(const std::string& text, std::queue<std::size_t>& indexes) const {
    isDocumentEmpty();
    if (text.empty()) {
        return;
    }
    for (std::size_t i = 0; i < document.size(); i++) {
        std::size_t pos = document[i].find(text);
        if (pos != std::string::npos) {
            indexes.push(i);
        }
    }
}

void TextEditor::addLine(const std::string& text) {
    saveState();
    document.push_back(text);
    setModified(true);
}

void TextEditor::editLine(const std::string& text, std::size_t index) {
    isDocumentEmpty();
    isIndexValid(index);
    saveState();
    document[index] = text;
    setModified(true);
}

void TextEditor::deleteLine(std::size_t index) {
    isDocumentEmpty();
    isIndexValid(index);
    saveState();
    document.erase(document.begin() + index);
    setModified(true);
}

void TextEditor::clearDocument() {
    isDocumentEmpty();
    saveState();
    document.clear();
    setModified(true);
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

bool TextEditor::hasCurrentFile() const {
    if (currentFile.empty()) {
        return false;
    }
    return true;
}

bool TextEditor::saveDocument() {
    return save(getCurrentFile());
}

bool TextEditor::saveAsDocument(const std::string& path) {
    return save(path);
}

bool TextEditor::save(const std::string& path) {
    std::ofstream file(path);
    if (!file) {
        return false;
    }
    setCurrentFile(path);
    for (std::size_t i = 0; i < document.size(); i++) {file << document[i] << std::endl;
    }
    setModified(false);
    return true;

}

bool TextEditor::loadDocument(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        return false;
    }
        document.clear();
        emptyRedoStack();
        emptyUndoStack();
        setCurrentFile(path);
        std::string line;
        while (std::getline(file, line)) {
            document.push_back(line);
        }
        setModified(false);
        return true;
}


bool TextEditor::replaceText(const std::string& text, const std::string& replaceWith, std::size_t line) {
    isDocumentEmpty();
    if (text.empty()) {
        return false;
    }
    isIndexValid(line);
    std::size_t pos = document[line].find(text);
    if (pos != std::string::npos) {
        saveState();
        setModified(true);
        document[line].replace(pos,text.length(),replaceWith);
        return true;
    }
    else {
        return false;
    }
}



bool TextEditor::replaceAllText(const std::string& text, const std::string& replaceWith) {
    isDocumentEmpty();
    if (text.empty()) {
        return false;
    }
    int replaced = 0;
    std::vector<std::string> backup = document;
    for (std::size_t i = 0; i < document.size(); i++) {
        bool textFound = false;
        std::size_t pos = 0;
        while ((pos = document[i].find(text,pos)) != std::string::npos) {
            document[i].replace(pos,text.length(),replaceWith);
            textFound = true;
            pos += replaceWith.length();
        }
            if (textFound) {
                replaced++;
            }
    }
    if (replaced == 0) {
        return false;
    }
    setModified(true);
    saveState(backup);
    return true;
}


DocumentStatistics TextEditor::getStatistics() const {
    isDocumentEmpty();
    std::size_t characters = 0;
    for (std::size_t i = 0; i < document.size(); i++) {
        characters += document[i].length();
    }
    return {characters,wordCounter(), document.size()};

}

//helper function
void TextEditor::isIndexValid(std::size_t index) const {
    if (index >= document.size()) {
        throw std::out_of_range("Index out of range");
    }
}

void TextEditor::isDocumentEmpty() const {
    if (document.empty()) {
        throw std::runtime_error("Document is empty");
    }
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

// Undo/Redo
void TextEditor::undo() {
    if (undoStack.empty()) {
        throw std::runtime_error("Undo stack is empty");
    }
    redoStack.push(document);
    document = undoStack.top();
    undoStack.pop();
    modified = true;
}

void TextEditor::redo() {
    if (redoStack.empty()) {
        throw std::runtime_error("Redo stack is empty");
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

void TextEditor::emptyUndoStack() {
    while (!undoStack.empty()) {
        undoStack.pop();
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