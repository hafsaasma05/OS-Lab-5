#include <windows.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "grandchild") == 0) {
        std::cout << "[Grandchild] PID: " << GetCurrentProcessId() << " | Parent: " << argv[2] << std::endl;
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        DWORD myPid = GetCurrentProcessId();
        char szPath[MAX_PATH];
        GetModuleFileNameA(NULL, szPath, MAX_PATH);
        char szCmdLine[MAX_PATH + 30];
        sprintf(szCmdLine, "\"%s\" grandchild %d", szPath, (int)myPid);

        STARTUPINFOA si; PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));
        CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess); CloseHandle(pi.hThread);

        std::cout << "[Child 1] PID: " << myPid << " | Parent: " << argv[2] << std::endl;
        return 0;
    }

    DWORD parentPid = GetCurrentProcessId();
    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 30];
    sprintf(szCmdLine, "\"%s\" child %d", szPath, (int)parentPid);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));
    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);

    std::cout << "[Parent] All descendants have completed.\n";
    return 0;
}