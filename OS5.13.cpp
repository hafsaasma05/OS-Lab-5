#include <windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "sub") == 0) {
        std::cout << "Sub-process running under supervisor control.\n";
        return 0;
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20]; sprintf(szCmdLine, "\"%s\" sub", szPath);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));

    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);

    std::cout << "Supervisor successfully tracked and reaped sub-process.\n";
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return 0;
}