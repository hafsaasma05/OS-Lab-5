#include <windows.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int counter = 100;

    // Agar yeh child process instance hai
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        counter = atoi(argv[2]); // Parent se value li
        counter += 50;           // Modify child copy
        std::cout << "[Child] counter = " << counter 
                  << " at address: " << &counter << std::endl;
        return 0;
    }

    // Parent process context
    char szPath[MAX_PATH];
    GetModuleFileNameA(NULL, szPath, MAX_PATH);

    char szCmdLine[MAX_PATH + 50];
    sprintf(szCmdLine, "\"%s\" child %d", szPath, counter);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Child process spawn kar rahe hain (Memory Isolation)
    if (!CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Process creation failed (" << GetLastError() << ").\n";
        return 1;
    }

    // Parent thori der wait karega
    Sleep(1000); 

    std::cout << "[Parent] counter = " << counter 
              << " at address: " << &counter << std::endl;

    // Parent wait karega child ke khatam hone ka
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Addresses appear similar (virtual), but values remain isolated in separate processes.\n";
    return 0;
}