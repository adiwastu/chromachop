#include "WebpScanner.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>

// Global flag for graceful shutdown
std::atomic<bool> keepRunning(true);

void signalHandler(int signal) {
    std::cout << "\nReceived signal " << signal << ". Shutting down gracefully..." << std::endl;
    keepRunning = false;
}

int main()
{
    // Set up signal handler for graceful shutdown (Ctrl+C)
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    std::string folderPath = "A:\\Downloads";
    WebpScanner scanner(folderPath);

    std::cout << "Starting continuous WebP monitoring on: " << folderPath << std::endl;
    std::cout << "Press Ctrl+C to stop..." << std::endl;

    int scanCount = 0;
    const int SCAN_INTERVAL_SECONDS = 10; // Check every 10 seconds

    while (keepRunning) {
        try {
            scanCount++;
            std::cout << "\n--- Scan #" << scanCount << " ---" << std::endl;
            scanner.scanAndConvert(); // Use the new method that tracks files

            // Sleep for the specified interval
            for (int i = 0; i < SCAN_INTERVAL_SECONDS && keepRunning; ++i) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error during scan: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait before retry
        }
    }

    std::cout << "Scanner stopped. Total scans performed: " << scanCount << std::endl;
    scanner.printStats(); // Show final stats
    return 0;
}