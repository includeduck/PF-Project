#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class FileManager {
private:
    std::string filename;

public:
    FileManager(const std::string& filename = "GameResults.txt");

    // Save game result to file
    void saveResult(const std::string& result);

    // Load and display previous game result
    void loadAndDisplayResult();
};

#endif


