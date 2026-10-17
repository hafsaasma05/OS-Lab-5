#include <windows.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        for (int i = 1; i <= 5; i++) {
            std::cout << "Child working... step " << i << std::endl;
            Sleep(500);
        }
        return 0;
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20]; sprintf(szCmdLine, "\"%s\" child", szPath);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));
    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    std::cout << "Parent waiting for child completion...\n";
    WaitForSingleObject(pi.hProcess, INFINITE);
    std::cout << "Parent resumed: Child terminated successfully.\n";

    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}