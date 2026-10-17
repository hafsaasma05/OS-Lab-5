#include <windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "worker") == 0) {
        while (true) { Sleep(100); } // Infinite loop simulation
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20]; sprintf(szCmdLine, "\"%s\" worker", szPath);

    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));

    CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    std::cout << "Watchdog waiting for task completion (3s timeout)...\n";
    DWORD result = WaitForSingleObject(pi.hProcess, 3000);

    if (result == WAIT_TIMEOUT) {
        std::cout << "Child exceeded time limit. Terminating process PID: " << pi.dwProcessId << std::endl;
        TerminateProcess(pi.hProcess, 1);
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}