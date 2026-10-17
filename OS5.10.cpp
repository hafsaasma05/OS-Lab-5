#include <windows.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        Sleep(2000);
        return 0;
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char szCmdLine[MAX_PATH + 20]; sprintf(szCmdLine, "\"%s\" child", szPath);

    std::vector<PROCESS_INFORMATION> children(3);
    for (int i = 0; i < 3; i++) {
        STARTUPINFOA si; ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si);
        CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &children[i]);
    }

    std::cout << "Parent monitoring children asynchronously...\n";
    int active = 3;
    while (active > 0) {
        for (int i = 0; i < 3; i++) {
            if (children[i].hProcess != NULL) {
                DWORD status;
                GetExitCodeProcess(children[i].hProcess, &status);
                if (status != STILL_ACTIVE) {
                    std::cout << "Reaped terminated child process ID: " << children[i].dwProcessId << std::endl;
                    CloseHandle(children[i].hProcess);
                    CloseHandle(children[i].hThread);
                    children[i].hProcess = NULL;
                    active--;
                }
            }
        }
        Sleep(500);
    }
    std::cout << "All children successfully reaped.\n";
    return 0;
}