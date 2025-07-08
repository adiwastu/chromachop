#include "WebpScanner.h"
#include <iostream>

int main()
{
    std::string folderPath = "A:\\Downloads";

    WebpScanner scanner(folderPath);
    scanner.printWebpFiles();

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}
