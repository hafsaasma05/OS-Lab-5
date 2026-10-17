#include <windows.h>
#include <iostream>

int main() {
    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));

    // Launching 'notepad.exe' as an external image replacement demonstration
    char cmd[] = "notepad.exe";
    if (CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cout << "Notepad launched successfully via process execution.\n";
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Process execution failed.\n";
    }
    return 0;
}