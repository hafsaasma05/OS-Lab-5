#include <windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        std::cout << "Child terminating immediately.\n";
        return 0;
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20]; sprintf(szCmdLine, "\"%s\" child", szPath);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));

    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    
    // Immediately close handles so OS reclaims kernel resources upon termination
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Parent detached from child; resources deallocated automatically.\n";
    Sleep(2000);
    return 0;
}