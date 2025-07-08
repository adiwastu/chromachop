#include "WebpConverter.h"
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <sstream>

bool WebpConverter::convert(const std::string& inputPath, const std::string& outputPath)
{
    // Use filesystem::path to properly handle Windows paths
    std::filesystem::path input(inputPath);
    std::filesystem::path output(outputPath);

    // Check if input file exists
    if (!std::filesystem::exists(input)) {
        std::cerr << "Error: Input file does not exist: " << inputPath << std::endl;
        return false;
    }

#ifdef _WIN32
    // For Windows, use the full path to dwebp.exe
    std::filesystem::path dwebpPath = std::filesystem::current_path().parent_path().parent_path().parent_path() / "tools" / "dwebp.exe";

    if (!std::filesystem::exists(dwebpPath)) {
        std::cerr << "Error: dwebp.exe not found at: " << dwebpPath << std::endl;
        return false;
    }

    // Construct command with proper Windows path handling
    std::ostringstream commandStream;
    commandStream << dwebpPath.string() << " \"" << input.string() << "\" -o \"" << output.string() << "\"";
    std::string command = commandStream.str();
#else
    // For Unix/Linux systems
    std::string command = "dwebp \"" + input.string() + "\" -o \"" + output.string() + "\"";
#endif

    std::cout << "Executing: " << command << std::endl;

    int result = std::system(command.c_str());

    if (result == 0)
    {
        std::cout << "Successfully converted: " << input.filename() << " -> " << output.filename() << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Conversion failed for: " << input.filename() << std::endl;
        std::cerr << "Command returned: " << result << std::endl;
        return false;
    }
}