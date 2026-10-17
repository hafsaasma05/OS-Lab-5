#include <windows.h>
#include <iostream>

int main() {
    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si); ZeroMemory(&pi, sizeof(pi));

    // Custom environment string block (must be double-null terminated)
    char envBlock[] = "LAB_MODULE=OS_PROC\0SEM=FALL2026\0\0";

    char cmd[] = "cmd.exe /c set LAB_MODULE";
    if (CreateProcessA(NULL, cmd, NULL, NULL, FALSE, CREATE_UNICODE_ENVIRONMENT, envBlock, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return 0;
}