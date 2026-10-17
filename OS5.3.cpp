#include <windows.h>
#include <iostream>
#include <stdio.h>

void SpawnChild(int id) {
    char szPath[MAX_PATH];
    GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20];
    sprintf(szCmdLine, "\"%s\" sibling %d", szPath, id);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "sibling") == 0) {
        std::cout << "Sibling " << argv[2] << " running with PID: " << GetCurrentProcessId() << std::endl;
        return 0;
    }

    std::cout << "Spawning First Sibling...\n";
    SpawnChild(1);

    std::cout << "Spawning Second Sibling...\n";
    SpawnChild(2);

    std::cout << "Parent reaped both siblings.\n";
    return 0;
}