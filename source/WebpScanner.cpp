#include "WebpScanner.h"
#include "WebpConverter.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

WebpScanner::WebpScanner(const std::string& directory)
    : targetDir(directory), processedFilesLog(directory + "/.webp_processed.log")
{
    loadProcessedFiles();
}

void WebpScanner::loadProcessedFiles()
{
    std::ifstream file(processedFilesLog);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            processedFiles.insert(line);
        }
    }
}

void WebpScanner::saveProcessedFile(const std::string& filepath) const
{
    processedFiles.insert(filepath);
    std::ofstream file(processedFilesLog, std::ios::app);
    file << filepath << std::endl;
}

void WebpScanner::printWebpFiles() const
{
    try
    {
        for (const auto& entry : fs::directory_iterator(targetDir))
        {
            if (entry.is_regular_file())
            {
                auto path = entry.path();
                if (path.extension() == ".webp")
                {
                    std::string input = path.string();
                    // Better way to change extension
                    auto outputPath = path;
                    outputPath.replace_extension(".jpg");
                    std::string output = outputPath.string();

                    std::cout << "Converting: " << input << " -> " << output << std::endl;
                    if (!WebpConverter::convert(input, output))
                    {
                        std::cerr << "Failed to convert: " << input << std::endl;
                    }
                }
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
}

void WebpScanner::scanAndConvert()
{
    int newFilesFound = 0;
    int totalWebpFiles = 0;

    try {
        for (const auto& entry : fs::directory_iterator(targetDir)) {
            if (entry.is_regular_file()) {
                auto path = entry.path();
                if (path.extension() == ".webp") {
                    totalWebpFiles++;
                    std::string input = path.string();

                    // Check if already processed
                    if (processedFiles.find(input) != processedFiles.end()) {
                        continue; // Skip already processed files
                    }

                    // Check if corresponding JPG already exists
                    auto outputPath = path;
                    outputPath.replace_extension(".jpg");
                    if (fs::exists(outputPath)) {
                        std::cout << "Output already exists, skipping: " << outputPath.filename() << std::endl;
                        saveProcessedFile(input);
                        continue;
                    }

                    std::string output = outputPath.string();
                    std::cout << "NEW FILE - Converting: " << path.filename() << " -> " << outputPath.filename() << std::endl;

                    if (WebpConverter::convert(input, output)) {
                        saveProcessedFile(input);
                        newFilesFound++;
                    }
                    else {
                        std::cerr << "Failed to convert: " << path.filename() << std::endl;
                    }
                }
            }
        }

        if (newFilesFound > 0) {
            std::cout << "Processed " << newFilesFound << " new files" << std::endl;
        }
        else {
            std::cout << "No new WebP files found (Total WebP files: " << totalWebpFiles << ")" << std::endl;
        }

    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
}

void WebpScanner::printStats() const
{
    std::cout << "Processed files count: " << processedFiles.size() << std::endl;
}