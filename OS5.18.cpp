#include <windows.h>
#include <iostream>
#include <fstream>

int main() {
    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "[Process Data logged successfully]\n";
        logFile.close();
        std::cout << "Log entry written successfully to log.txt\n";
    }
    return 0;
}