#include "WebpScanner.h"
#include "WebpConverter.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

WebpScanner::WebpScanner(const std::string& directory) : targetDir(directory)
{}

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