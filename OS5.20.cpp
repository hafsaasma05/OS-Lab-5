#include <windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "c1") == 0) return 0;
        if (strcmp(argv[1], "c2") == 0) return 15;
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char cmd1[MAX_PATH + 20], cmd2[MAX_PATH + 20];
    sprintf(cmd1, "\"%s\" c1", szPath);
    sprintf(cmd2, "\"%s\" c2", szPath);

    STARTUPINFOA si1, si2; PROCESS_INFORMATION pi1, pi2;
    ZeroMemory(&si1, sizeof(si1)); si1.cb = sizeof(si1); ZeroMemory(&pi1, sizeof(pi1));
    ZeroMemory(&si2, sizeof(si2)); si2.cb = sizeof(si2); ZeroMemory(&pi2, sizeof(pi2));

    CreateProcessA(NULL, cmd1, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1);
    CreateProcessA(NULL, cmd2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2);

    PROCESS_INFORMATION pis[] = {pi1, pi2};
    for (int i = 0; i < 2; i++) {
        WaitForSingleObject(pis[i].hProcess, INFINITE);
        DWORD exitCode;
        GetExitCodeProcess(pis[i].hProcess, &exitCode);
        std::cout << "Harvested PID: " << pis[i].dwProcessId << " -> Clean termination with exit code: " << exitCode << std::endl;
        CloseHandle(pis[i].hProcess);
        CloseHandle(pis[i].hThread);
    }
    return 0;
}