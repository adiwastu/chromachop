#pragma once

#include <string>

class WebpScanner
{
public:
    explicit WebpScanner(const std::string& directory);
    void printWebpFiles() const;

private:
    std::string targetDir;
};
