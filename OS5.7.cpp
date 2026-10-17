#include <windows.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "childA") == 0) { Sleep(4000); return 10; }
        if (strcmp(argv[1], "childB") == 0) { Sleep(1000); return 20; }
    }

    char szPath[MAX_PATH]; GetModuleFileNameA(NULL, szPath, MAX_PATH);
    char cmdA[MAX_PATH + 20], cmdB[MAX_PATH + 20];
    sprintf(cmdA, "\"%s\" childA", szPath);
    sprintf(cmdB, "\"%s\" childB", szPath);

    STARTUPINFOA siA, siB; PROCESS_INFORMATION piA, piB;
    ZeroMemory(&siA, sizeof(siA)); siA.cb = sizeof(siA); ZeroMemory(&piA, sizeof(piA));
    ZeroMemory(&siB, sizeof(siB)); siB.cb = sizeof(siB); ZeroMemory(&piB, sizeof(piB));

    CreateProcessA(NULL, cmdA, NULL, NULL, FALSE, 0, NULL, NULL, &siA, &piA);
    CreateProcessA(NULL, cmdB, NULL, NULL, FALSE, 0, NULL, NULL, &siB, &piB);

    // Wait specifically for Child A first
    WaitForSingleObject(piA.hProcess, INFINITE);
    DWORD codeA; GetExitCodeProcess(piA.hProcess, &codeA);
    std::cout << "Child A reaped with status: " << codeA << std::endl;

    // Now wait for Child B
    WaitForSingleObject(piB.hProcess, INFINITE);
    DWORD codeB; GetExitCodeProcess(piB.hProcess, &codeB);
    std::cout << "Child B reaped with status: " << codeB << std::endl;

    CloseHandle(piA.hProcess); CloseHandle(piA.hThread);
    CloseHandle(piB.hProcess); CloseHandle(piB.hThread);
    return 0;
}