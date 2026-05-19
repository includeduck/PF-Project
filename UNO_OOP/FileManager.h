#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
using namespace std;

class FileManager {
private:
    string filename;

public:
    FileManager(const string& filename = "GameResults.txt");

    // Save game result to file
    void saveResult(const string& result);

    // Load and display previous game result
    void loadAndDisplayResult();
};

#endif
