#include "WebpScanner.h"
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
                    std::cout << path.filename().string() << std::endl;
                }
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
}
