#include <windows.h>
#include <iostream>
#include <string>

int main() {
    std::string input;
    while (true) {
        std::cout << "myshell> ";
        std::getline(std::cin, input);
        if (input == "exit" || input.empty()) break;

        STARTUPINFOA si; PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));

        char cmd[256]; strcpy(cmd, input.c_str());
        if (CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } else {
            std::cout << "Command execution failed.\n";
        }
    }
    return 0;
}