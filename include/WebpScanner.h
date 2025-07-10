#pragma once
#include <string>
#include <unordered_set>

class WebpScanner
{
public:
    explicit WebpScanner(const std::string& directory);
    void printWebpFiles() const;
    void scanAndConvert(); // New method for one-time scan with file tracking
    void printStats() const; // New method to show processed files count

private:
    std::string targetDir;
    mutable std::unordered_set<std::string> processedFiles; // Track processed files
    std::string processedFilesLog; // Log file path

    void loadProcessedFiles(); // Load previously processed files
    void saveProcessedFile(const std::string& filepath) const; // Save processed file to log
};