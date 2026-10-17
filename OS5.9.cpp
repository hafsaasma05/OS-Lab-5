#include <windows.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        std::cout << "Child exiting immediately (PID: " << GetCurrentProcessId() << ").\n";
        return 0;
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20]; sprintf(szCmdLine, "\"%s\" child", szPath);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));

    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    
    std::cout << "Parent sleeping 5s while child terminates (holding process handle open).\n";
    Sleep(5000); // Child terminates, but handle remains open (retaining resource table entry)

    WaitForSingleObject(pi.hProcess, INFINITE);
    std::cout << "Process handle closed and reaped.\n";

    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}