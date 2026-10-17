#include <windows.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        Sleep(3000);
        return 0;
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20]; sprintf(szCmdLine, "\"%s\" child", szPath);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));
    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    DWORD exitCode;
    while (true) {
        GetExitCodeProcess(pi.hProcess, &exitCode);
        if (exitCode == STILL_ACTIVE) {
            std::cout << "Parent computing independent background tasks...\n";
            Sleep(500);
        } else {
            std::cout << "Child finished! Parent wrapping up.\n";
            break;
        }
    }

    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}