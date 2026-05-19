#include "FileManager.h"
#include <iostream>
#include <fstream>
using namespace std;

FileManager::FileManager(const string& filename) : filename(filename) {}

void FileManager::saveResult(const string& result) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << result << endl;
        outFile.close();
        cout << "Game results saved successfully!" << endl;
    } else {
        cerr << "Can't Open File" << endl;
    }
}

void FileManager::loadAndDisplayResult() {
    cout << "Previous Game Result: " << endl;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string gameResult;
        while (getline(inFile, gameResult)) {
            cout << gameResult << endl;
        }
        inFile.close();
    } else {
        cerr << "Can't Open File" << endl;
    }
}
