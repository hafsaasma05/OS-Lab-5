#include <windows.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Agar yeh child process instance hai (command line argument ke zariye check hoga)
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        std::cout << "Child Process-> PID: " << GetCurrentProcessId() 
                  << " | Parent PID: " << atoi(argv[2]) << std::endl;
        return 0;
    }

    // Parent process context
    DWORD parentPid = GetCurrentProcessId();
    
    char szPath[MAX_PATH];
    GetModuleFileNameA(NULL, szPath, MAX_PATH);

    char szCmdLine[MAX_PATH + 30];
    sprintf(szCmdLine, "\"%s\" child %d", szPath, (int)parentPid);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Windows mein fork ki jagah CreateProcess use hota hai
    if (!CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Process creation failed (" << GetLastError() << ").\n";
        return 1;
    }

    std::cout << "Parent Process-> PID: " << parentPid << " | Child PID: " << pi.dwProcessId << std::endl;

    // Parent wait karega jab tak child mukamal na ho jaye (wait() ki tarah)
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Handles close karna zaroori hai
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}